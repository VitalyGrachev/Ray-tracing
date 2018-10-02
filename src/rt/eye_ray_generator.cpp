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
    return std::make_optional<EyeRay>({ray, fragment});
}

Ray EyeRayGenerator::fragment_ray(const Vec2 & angles) const {
    const float tan_x = std::tan(angles.x());
    const float tan_y = std::tan(angles.y());
    const Transform & tr = camera_.transform();
    return Ray(tr.origin(), tr.forward() + tan_x * tr.left() + tan_y * tr.up());
}

Vec2 EyeRayGenerator::fragment_angles(FrameBuffer::Position fragment_pos) const {
    const FrameBuffer::Size & size = frame_buffer_.size();
    return camera_.field_of_view() * Vec2(0.5f - (0.5f + fragment_pos.col) / size.cols,
                                          0.5f - (0.5f + fragment_pos.row) / size.rows);
}

std::optional<FrameBuffer::Position> EyeRayGenerator::next_fragment_position() {
    const FrameBuffer::Size & size = frame_buffer_.size();

    if (!frame_buffer_.is_position_valid(next_fragment_pos_)) { return std::nullopt; }

    const FrameBuffer::Position fragment_pos = next_fragment_pos_;

    next_fragment_pos_.row += (next_fragment_pos_.col + 1) / size.cols;
    next_fragment_pos_.col = (next_fragment_pos_.col + 1) % size.cols;

    return std::optional<FrameBuffer::Position>(fragment_pos);
}
