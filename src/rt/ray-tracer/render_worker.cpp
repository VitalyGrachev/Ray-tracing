#include "render_worker.h"

RenderWorker::RenderWorker(const std::shared_ptr<FrameRenderer> & frame_render)
        : frame_render_(frame_render) {}

void RenderWorker::operator()() {
    while (auto task = frame_render_->get_task()) {
        task->operator()(*frame_render_);
    }
}
