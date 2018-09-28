#include "eye_ray_generator.h"

#include <cmath>

#include "../geometry/ray_transform.h"

EyeRayGenerator::EyeRayGenerator(FrameBuffer & frame_buffer,
                                 const Camera & camera)
        : frame_buffer_(frame_buffer),
          next_fragment_pos_({0, 0}),
          camera_(camera) {}

std::optional<EyeRayGenerator::EyeRay> EyeRayGenerator::next_eye_ray() {
    auto fragment_position = next_fragment_position();
    if (!fragment_position) { return std::nullopt; }

    Color & fragment = frame_buffer_.color_at(*fragment_position);
    const Ray ray = fragment_ray(fragment_angles(*fragment_position));
    return std::make_optional<EyeRay>(ray, fragment);
}

Ray EyeRayGenerator::fragment_ray(const Vec2 & angles) const {
    const float cos_x = std::cos(angles.x());
    const float cos_y = std::cos(angles.y());
    const float sin_x = std::sin(angles.x());
    const float sin_y = std::sin(angles.y());
    const Transform & tr = camera_.transform();
    return Ray(tr.origin(), cos_y * cos_x * tr.forward() + cos_y * sin_x * tr.left() + sin_y * tr.up());
}

Vec2 EyeRayGenerator::fragment_angles(FrameBuffer::Position fragment_pos) const {
    const FrameBuffer::Size & size = frame_buffer_.size();
    return camera_.field_of_view() * Vec2((0.5f + fragment_pos.col) / size.cols - 0.5f,
                                          (0.5f + fragment_pos.row) / size.rows - 0.5f);
}

std::optional<FrameBuffer::Position> EyeRayGenerator::next_fragment_position() {
    const FrameBuffer::Size & size = frame_buffer_.size();

    if (!frame_buffer_.is_position_valid(next_fragment_pos_)) { return std::nullopt; }

    const FrameBuffer::Position fragment_pos = next_fragment_pos_;

    next_fragment_pos_.row += (next_fragment_pos_.col + 1) / size.cols;
    next_fragment_pos_.col = (next_fragment_pos_.col + 1) % size.cols;

    return std::optional<FrameBuffer::Position>(fragment_pos);
}
