#ifndef RAY_TRACING_RENDER_WORKER_H
#define RAY_TRACING_RENDER_WORKER_H

#include "frame_renderer.h"

class RenderWorker {
public:
    explicit RenderWorker(const std::shared_ptr<FrameRenderer> & frame_render);

    void operator()();

private:
    std::shared_ptr<FrameRenderer> frame_render_;
};

#endif //RAY_TRACING_RENDER_WORKER_H
