#ifndef RAY_TRACING_RENDER_H
#define RAY_TRACING_RENDER_H

#include <future>

#include "frame/frame_buffer.h"
#include "../scene/scene.h"

std::future<FrameBuffer> render(const std::shared_ptr<Scene> & scene, FrameBuffer && frame_buffer);

#endif //RAY_TRACING_RENDER_H
