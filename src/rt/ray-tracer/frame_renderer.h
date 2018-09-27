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
#include "../eye_ray_generator.h"
#include "util/eye_ray_trace_task_factory.h"

class FrameRenderer : public RayTracer {
public:
    using Task = std::unique_ptr<RayTraceTask>;

    FrameRenderer(const std::shared_ptr<const Scene> & scene, FrameBuffer && frame_buffer);

    Task get_task();

    void trace_ray(std::unique_ptr<RayTraceTask> && ray) override;

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
