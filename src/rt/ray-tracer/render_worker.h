#ifndef RAY_TRACING_RENDER_WORKER_H
#define RAY_TRACING_RENDER_WORKER_H

#include "frame_renderer.h"

/**
 * Functor to be executed in worker thread.
 */
class RenderWorker {
public:
    explicit RenderWorker(const std::shared_ptr<FrameRenderer> & frame_renderer);

    void operator()();

private:
    std::shared_ptr<FrameRenderer> frame_renderer_;
};

#endif //RAY_TRACING_RENDER_WORKER_H
