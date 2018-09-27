#include "air_ray_trace_task.h"

#include <functional>

#include "shadow_ray_trace_task.h"

namespace {
constexpr float bias = 0.0000001f;
}

AirRayTraceTask::AirRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                                 const Ray & ray,
                                 const Scene & scene,
                                 const Color & color_intensity,
                                 unsigned int max_recursion_depth)
        : BaseRayTraceTask(fragment, scene, ray, color_intensity),
          remaining_recursion_depth_(max_recursion_depth) {}

AirRayTraceTask::AirRayTraceTask(const AirRayTraceTask & parent, const Ray & ray, const Color & color_intensity)
        : BaseRayTraceTask(parent, ray, color_intensity),
          remaining_recursion_depth_(parent.remaining_recursion_depth_ - 1) {}

void AirRayTraceTask::operator()(RayTracer & ray_tracer) {
    auto intersection_target = scene().find_intersection(ray());
    if (!intersection_target) { return; }

    const Intersection & intersection = intersection_target->intersection();
    const Object & object = intersection_target->target();
    const BRDFunction surface_brdf = object.material().brdf_at(intersection.tex_coords());

    emit_shadow_rays(intersection, surface_brdf, ray_tracer);

    if (remaining_recursion_depth_ <= 0) { return; }

    emit_refracted_ray(intersection, surface_brdf, ray_tracer);
}

void AirRayTraceTask::emit_shadow_rays(const Intersection & intersection,
                                       const BRDFunction & surface_brdf,
                                       RayTracer & ray_tracer) {
    const Vec3 & surface_normal = intersection.normal();
    for (const LightSource & light_source : scene().enumerate_light_sources()) {
        const Illuminance illuminance = light_source.illuminate_point(intersection.point());
        ray_tracer.trace_ray(std::make_unique<ShadowRayTraceTask>(*this,
                                                                  illuminance,
                                                                  std::bind(surface_brdf,
                                                                            -ray().direction(),
                                                                            std::placeholders::_1,
                                                                            surface_normal)));
    }
}

void AirRayTraceTask::emit_refracted_ray(const Intersection & intersection,
                                         const BRDFunction & surface_brdf,
                                         RayTracer & ray_tracer) {
    const Vec3 & surface_normal = intersection.normal();
    const Vec3 reflectance_dir = ray().direction() +
                                 2.0f * Vec3::dotProduct(ray().direction(), surface_normal) * surface_normal;
    const Ray reflected_ray(intersection.point() + bias * reflectance_dir, reflectance_dir);
    const Color & incoming_intensity = surface_brdf(-ray().direction(), reflected_ray.direction(), surface_normal);
    ray_tracer.trace_ray(std::make_unique<AirRayTraceTask>(*this, reflected_ray, incoming_intensity));
}
