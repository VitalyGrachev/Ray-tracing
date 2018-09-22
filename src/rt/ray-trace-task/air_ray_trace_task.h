#ifndef RAY_TRACING_AIR_RAY_TRACE_TASK_H
#define RAY_TRACING_AIR_RAY_TRACE_TASK_H

#include "base_ray_trace_task.h"
#include "../ray-tracer/ray_tracer.h"

class AirRayTraceTask : public BaseRayTraceTask {
public:
    AirRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                    const std::shared_ptr<RayTracer> & ray_tracer,
                    const Ray & ray,
                    const Scene & scene,
                    const Color & color_intensity,
                    unsigned int max_recursion_depth);

    void operator()() override;

private:
    AirRayTraceTask(const AirRayTraceTask & parent, const Ray & ray, const Color & color_intensity);

    void emit_shadow_rays(const Intersection & intersection, const BRDFunction & surface_brdf);

    void emit_refracted_ray(const Intersection & intersection, const BRDFunction & surface_brdf);

    std::shared_ptr<RayTracer> ray_tracer_;
    unsigned int remaining_recursion_depth_;
};

#endif //RAY_TRACING_AIR_RAY_TRACE_TASK_H
