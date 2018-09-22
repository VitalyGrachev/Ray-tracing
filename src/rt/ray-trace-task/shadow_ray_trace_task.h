#ifndef RAY_TRACING_SHADOW_RAY_TRACE_TASK_H
#define RAY_TRACING_SHADOW_RAY_TRACE_TASK_H

#include "base_ray_trace_task.h"

class ShadowRayTraceTask : public BaseRayTraceTask {
public:
    using BRDF = std::function<Color(const Vec3 & light_dir)>;

    ShadowRayTraceTask(const BaseRayTraceTask & parent, const Illuminance & illuminance, const BRDF & surface_brdf);

    void operator()() override;

private:
    BRDF surface_brdf_;
    Color illuminance_;
    float distance_to_source_;
};

#endif //RAY_TRACING_SHADOW_RAY_TRACE_TASK_H
