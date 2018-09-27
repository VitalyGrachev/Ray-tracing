#ifndef RAY_TRACING_AIR_RAY_TRACE_TASK_H
#define RAY_TRACING_AIR_RAY_TRACE_TASK_H

#include "base_ray_trace_task.h"
#include "../ray_tracer.h"

class AirRayTraceTask : public BaseRayTraceTask {
public:
    AirRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                    const Ray & ray,
                    const Scene & scene,
                    const Color & color_intensity,
                    unsigned int max_recursion_depth);

    void operator()(RayTracer & ray_tracer) override;

private:
    AirRayTraceTask(const AirRayTraceTask & parent, const Ray & ray, const Color & color_intensity);

    void emit_shadow_rays(const Intersection & intersection,
                          const BRDFunction & surface_brdf,
                          RayTracer & ray_tracer);

    void emit_refracted_ray(const Intersection & intersection,
                            const BRDFunction & surface_brdf,
                            RayTracer & ray_tracer);

    unsigned int remaining_recursion_depth_;
};

#endif //RAY_TRACING_AIR_RAY_TRACE_TASK_H
