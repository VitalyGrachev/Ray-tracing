#include "render_worker.h"

RenderWorker::RenderWorker(const std::shared_ptr<FrameRenderer> & frame_renderer)
        : frame_renderer_(frame_renderer) {}

void RenderWorker::operator()() {
    while (auto task = frame_renderer_->get_task()) {
        task->operator()(*frame_renderer_);
    }
}
