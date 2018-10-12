#ifndef RAY_TRACING_AIR_RAY_TRACE_TASK_H
#define RAY_TRACING_AIR_RAY_TRACE_TASK_H

#include "base_ray_trace_task.h"
#include "../ray_tracer.h"

/**
 * Trace task for a ray traveling through the air.
 * Generates recursive rays when hits object surface.
 */
class AirRayTraceTask : public BaseRayTraceTask {
public:
    /**
     * Creates air ray trace task
     * @param fragment fragment of render buffer to accumulate ray color
     * @param ray ray to trace
     * @param scene scene which is being rendered
     * @param color_intensity intensity of color added to fragment by this ray trace
     * @param max_recursion_depth max depth of child ray tree
     */
    AirRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                    const Ray & ray,
                    const Scene & scene,
                    const Color & color_intensity,
                    unsigned int max_recursion_depth);

    /**
     * Creates air ray trace task from parent air ray trace task
     * @param parent
     * @param ray
     * @param color_intensity
     */
    AirRayTraceTask(const AirRayTraceTask & parent, const Ray & ray, const Color & color_intensity);

    /**
     * Performs this task
     * @param ray_tracer ray tracer to trace child rays
     */
    void operator()(RayTracer & ray_tracer) override;

private:
    void emit_shadow_rays(const Intersection & intersection,
                          const BRDFunction & surface_brdf,
                          RayTracer & ray_tracer);

    void emit_refracted_ray(const Intersection & intersection,
                            const BRDFunction & surface_brdf,
                            RayTracer & ray_tracer);

    unsigned int remaining_recursion_depth_;
};

#endif //RAY_TRACING_AIR_RAY_TRACE_TASK_H
