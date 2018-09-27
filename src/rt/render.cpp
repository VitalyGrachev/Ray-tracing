#include "render.h"

#include <thread>
#include "ray-tracer/frame_renderer.h"
#include "ray-tracer/render_worker.h"

std::future<FrameBuffer> render(const std::shared_ptr<Scene> & scene, FrameBuffer && frame_buffer) {
    auto frame_renderer = std::make_shared<FrameRenderer>(scene, std::move(frame_buffer));
    auto future_frame = frame_renderer->future_frame();

    const unsigned num_threads = std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 2;
    for (unsigned i = 0; i < num_threads; ++i) {
        std::thread t = std::thread(RenderWorker(frame_renderer));
        t.detach();
    }

    return future_frame;
}
