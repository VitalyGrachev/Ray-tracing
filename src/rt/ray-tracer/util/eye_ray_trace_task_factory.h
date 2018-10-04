#ifndef RAY_TRACING_EYE_RAY_TRACE_TASK_FACTORY_H
#define RAY_TRACING_EYE_RAY_TRACE_TASK_FACTORY_H

#include <functional>
#include <memory>

#include "../ray-trace-task/ray_trace_task.h"
#include "../../../geometry/ray.h"
#include "../../../scene/scene.h"
#include "../../frame/fragment.h"
#include "../ray_tracer.h"

class EyeRayTraceTaskFactory {
public:
    EyeRayTraceTaskFactory(const Scene & scene, const Color & color_intensity, unsigned int max_recursion_depth);

    std::unique_ptr<RayTraceTask> create(const Ray & ray, const std::shared_ptr<Fragment> & fragment);

private:
    const Scene & scene_;
    Color color_intensity_;
    unsigned int max_recursion_depth_;
};

#endif //RAY_TRACING_EYE_RAY_TRACE_TASK_FACTORY_H
