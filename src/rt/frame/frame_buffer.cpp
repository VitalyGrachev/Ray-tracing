#include "frame_buffer.h"

FrameBuffer::FrameBuffer(const Size & size)
        : fragment_colors_(size.cols * size.rows, Color(0, 0, 0)),
          size_(size) {}

FrameBuffer::FrameBuffer(FrameBuffer && other) noexcept
        : fragment_colors_(std::move(other.fragment_colors_)),
          size_(other.size_) {
    other.size_ = {0, 0};
}

FrameBuffer & FrameBuffer::operator=(FrameBuffer && other) noexcept {
    if (this == &other) return *this;

    fragment_colors_ = std::move(other.fragment_colors_);
    size_ = other.size_;

    other.size_ = {0, 0};
    return *this;
}
