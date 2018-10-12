#ifndef RAY_TRACING_FRAME_RENDERER_H
#define RAY_TRACING_FRAME_RENDERER_H

#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <queue>

#include "util/finished_fragment_counter.h"
#include "ray_tracer.h"
#include "../frame/frame_buffer.h"
#include "../../scene/scene.h"
#include "util/eye_ray_generator.h"
#include "util/eye_ray_trace_task_factory.h"

/**
 * Entity which handles rendering of scene into frame buffer
 */
class FrameRenderer : public RayTracer {
public:
    using Task = std::unique_ptr<RayTraceTask>;

    /**
     * Creates frame renderer which renders given scene into given frame buffer
     * @param scene scene to render
     * @param frame_buffer frame buffer to render into
     */
    FrameRenderer(const std::shared_ptr<const Scene> & scene, FrameBuffer && frame_buffer);

    /**
     * @return next task to perform or nullptr, if render is finished
     */
    Task get_task();

    /**
     * Puts given task into a queue to eventually return a task to perform
     * @param ray ray trace task to eventually perform
     */
    void trace_ray(std::unique_ptr<RayTraceTask> && ray) override;

    /**
     * @return std::future which resolves into resulting frame buffer, when render finishes
     */
    std::future<FrameBuffer> future_frame();

private:
    using TaskQueue = std::queue<std::unique_ptr<RayTraceTask>>;

    Task get_task_from_queue(TaskQueue & queue);

    Task generate_eye_ray_task();

    std::promise<FrameBuffer> frame_promise_;
    FrameBuffer frame_buffer_;
    std::shared_ptr<const Scene> scene_;

    EyeRayGenerator eye_ray_generator_;
    TaskQueue shadow_ray_tasks_;
    TaskQueue air_ray_tasks_;
    FinishedFragmentCounter finished_fragment_counter_;
    EyeRayTraceTaskFactory eye_ray_trace_task_factory_;

    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif //RAY_TRACING_FRAME_RENDERER_H
