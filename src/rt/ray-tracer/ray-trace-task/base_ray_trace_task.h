#ifndef RAY_TRACING_BASE_RAY_TRACE_TASK_H
#define RAY_TRACING_BASE_RAY_TRACE_TASK_H

#include "ray_trace_task.h"
#include "../../frame/fragment.h"
#include "../../../util/color.h"
#include "../../../scene/scene.h"

class BaseRayTraceTask : public RayTraceTask {
public:
    BaseRayTraceTask(const BaseRayTraceTask & other) = delete;

    ~BaseRayTraceTask() = default;

    BaseRayTraceTask & operator=(const BaseRayTraceTask & other) = delete;

protected:
    BaseRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                     const Scene & scene,
                     const Ray & ray,
                     const Color & color_intensity);

    BaseRayTraceTask(const BaseRayTraceTask & parent, const Ray & ray, const Color & color_intensity);

    void submit_color(const Color & color);

    const Scene & scene() const { return scene_; }

    const Ray & ray() const { return ray_; }

private:
    Ray ray_;
    Color color_intensity_;
    std::shared_ptr<Fragment> fragment_;
    std::reference_wrapper<const Scene> scene_;
};

#endif //RAY_TRACING_BASE_RAY_TRACE_TASK_H
