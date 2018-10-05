#ifndef RAY_TRACING_RENDER_H
#define RAY_TRACING_RENDER_H

#include <future>

#include "frame/frame_buffer.h"
#include "../scene/scene.h"

/**
 * Asynchronously renders given scene into given frame buffer.
 * @param scene scene to render, MUST NOT be changed until render finished
 * @param frame_buffer frame buffer to store colors to
 * @return std::future which resolves into resulting frame buffer, when render finishes
 */
std::future<FrameBuffer> render(const std::shared_ptr<Scene> & scene, FrameBuffer && frame_buffer);

#endif //RAY_TRACING_RENDER_H
