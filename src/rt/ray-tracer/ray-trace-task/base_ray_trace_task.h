#ifndef RAY_TRACING_BASE_RAY_TRACE_TASK_H
#define RAY_TRACING_BASE_RAY_TRACE_TASK_H

#include "ray_trace_task.h"
#include "../../frame/fragment.h"
#include "../../../util/color.h"
#include "../../../scene/scene.h"

/**
 * Base class for ray trace tasks.
 */
class BaseRayTraceTask : public RayTraceTask {
public:
    BaseRayTraceTask(const BaseRayTraceTask & other) = delete;

    ~BaseRayTraceTask() = default;

    BaseRayTraceTask & operator=(const BaseRayTraceTask & other) = delete;

protected:
    /**
     * Creates trace task for given ray
     * @param fragment fragment of render buffer to accumulate ray color
     * @param scene scene which is being rendered
     * @param ray ray to trace
     * @param color_intensity intensity of color added to fragment by this ray trace
     */
    BaseRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                     const Scene & scene,
                     const Ray & ray,
                     const Color & color_intensity);

    /**
     * Creates trace task for given from the parent base ray trace task
     * @param parent parent ray trace task, shares scene and fragment with this trace task
     * @param ray ray to trace
     * @param color_intensity intensity of color added to parents contribution to fragment by this ray trace
     */
    BaseRayTraceTask(const BaseRayTraceTask & parent, const Ray & ray, const Color & color_intensity);

    /**
     * Submits this ray's color to fragment
     * @param color ray's color
     */
    void submit_color(const Color & color);

    /**
     * @return scene which is being rendered
     */
    const Scene & scene() const { return scene_; }

    /**
     * @return ray which is being traced
     */
    const Ray & ray() const { return ray_; }

private:
    Ray ray_;
    Color color_intensity_;
    std::shared_ptr<Fragment> fragment_;
    std::reference_wrapper<const Scene> scene_;
};

#endif //RAY_TRACING_BASE_RAY_TRACE_TASK_H
