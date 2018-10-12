#ifndef RAY_TRACING_RENDER_WORKER_H
#define RAY_TRACING_RENDER_WORKER_H

#include "frame_renderer.h"

/**
 * Functor to be executed in worker thread.
 */
class RenderWorker {
public:
    /**
     * Creates render worker which gets tasks from given frame renderer
     * @param frame_renderer task provider
     */
    explicit RenderWorker(const std::shared_ptr<FrameRenderer> & frame_renderer);

    /**
     * Performs tasks provided by frame renderer
     */
    void operator()();

private:
    std::shared_ptr<FrameRenderer> frame_renderer_;
};

#endif //RAY_TRACING_RENDER_WORKER_H
