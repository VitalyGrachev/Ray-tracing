#ifndef RAY_TRACING_EYE_RAY_GENERATOR_H
#define RAY_TRACING_EYE_RAY_GENERATOR_H

#include <functional>
#include <memory>

#include "../../frame/frame_buffer.h"
#include "../../../geometry/ray.h"
#include "../../../scene/camera/camera.h"

class EyeRayGenerator final {
public:
    struct EyeRay {
        Ray ray;
        std::reference_wrapper<Color> acceptor_fragment;
    };

    EyeRayGenerator(FrameBuffer & frame_buffer, const Camera & camera);

    EyeRayGenerator(const EyeRayGenerator & other) = delete;

    ~EyeRayGenerator() = default;

    EyeRayGenerator & operator=(const EyeRayGenerator & other) = delete;

    std::optional<EyeRay> next_eye_ray();

private:
    Vec2 fragment_angles(FrameBuffer::Position fragment_pos) const;

    Ray fragment_ray(const Vec2 & angles) const;

    std::optional<FrameBuffer::Position> next_fragment_position();

    FrameBuffer::Position next_fragment_pos_;
    FrameBuffer & frame_buffer_;
    const Camera & camera_;
};

#endif //RAY_TRACING_EYE_RAY_GENERATOR_H
