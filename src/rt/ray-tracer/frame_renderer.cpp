#include "frame_renderer.h"

#include <typeinfo>
#include <typeindex>

#include "ray-trace-task/shadow_ray_trace_task.h"
#include "util/fragment_render_task.h"

namespace {
const std::type_index shadow_ray_type = typeid(ShadowRayTraceTask);
}

FrameRenderer::FrameRenderer(const std::shared_ptr<const Scene> & scene, FrameBuffer && frame_buffer)
        : frame_buffer_(std::move(frame_buffer)),
          scene_(scene),
          eye_ray_generator_(frame_buffer_, scene_->get_camera()),
          finished_fragment_counter_(frame_buffer.size().rows * frame_buffer.size().cols, [&]() {
              frame_promise_.set_value(std::move(frame_buffer_));

              std::lock_guard lock(mutex_);
              cond_.notify_all();
          }),
          eye_ray_trace_task_factory_(*scene_, Color(1, 1, 1), 5) {}

FrameRenderer::Task FrameRenderer::get_task() {
    std::unique_lock lock(mutex_);
    while (!finished_fragment_counter_.is_render_finished()) {
        if (auto task = get_task_from_queue(shadow_ray_tasks_)) {
            return task;
        }

        if (auto task = get_task_from_queue(air_ray_tasks_)) {
            return task;
        }

        if (auto task = generate_eye_ray_task()) {
            return task;
        }

        cond_.wait(lock);
    }
    return nullptr;
}

std::future<FrameBuffer> FrameRenderer::future_frame() {
    return frame_promise_.get_future();
}

FrameRenderer::Task FrameRenderer::get_task_from_queue(FrameRenderer::TaskQueue & queue) {
    if (queue.empty()) { return nullptr; }

    auto task = std::move(queue.front());
    queue.pop();
    return task;
}

FrameRenderer::Task FrameRenderer::generate_eye_ray_task() {
    auto eye_ray = eye_ray_generator_.next_eye_ray();
    if (!eye_ray) { return nullptr; }

    return eye_ray_trace_task_factory_.create(eye_ray->ray,
                                              std::make_shared<FragmentRenderTask>(*this, eye_ray->acceptor_fragment));
}

void FrameRenderer::trace_ray(std::unique_ptr<RayTraceTask> && ray) {
    const std::type_index ray_type = typeid(ray);

    std::lock_guard lock(mutex_);
    if (ray_type == shadow_ray_type) {
        shadow_ray_tasks_.emplace(std::move(ray));
    } else {
        air_ray_tasks_.emplace(std::move(ray));
    }
}
