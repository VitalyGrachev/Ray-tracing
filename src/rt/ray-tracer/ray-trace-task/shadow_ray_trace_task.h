#ifndef RAY_TRACING_SHADOW_RAY_TRACE_TASK_H
#define RAY_TRACING_SHADOW_RAY_TRACE_TASK_H

#include "base_ray_trace_task.h"

/**
 * Trace task for a ray from surface point to light source.
 * Determines, if point is lit by light source or is shadowed by some object.
 */
class ShadowRayTraceTask : public BaseRayTraceTask {
public:
    using BRDF = std::function<Color(const Vec3 & light_dir)>;

    /**
     * Creates shadow ray trace task
     * @param parent parent ray trace task, shares scene and fragment with this trace task
     * @param illuminance illuminance created by light source in surface point
     * @param surface_brdf function, which determines amount of light submitted by this for given direction to light source
     */
    ShadowRayTraceTask(const BaseRayTraceTask & parent, const Illuminance & illuminance, const BRDF & surface_brdf);

    /**
     * Performs this task
     * @param ray_tracer ray tracer to trace child rays
     */
    void operator()(RayTracer & ray_tracer) override;

private:
    BRDF surface_brdf_;
    Color illuminance_;
    float distance_to_source_;
};

#endif //RAY_TRACING_SHADOW_RAY_TRACE_TASK_H
