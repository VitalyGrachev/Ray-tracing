#ifndef RAY_TRACING_FRAME_BUFFER_H
#define RAY_TRACING_FRAME_BUFFER_H

#include <vector>
#include "../../util/color.h"

class FrameBuffer {
public:
    struct Size {
        unsigned cols;
        unsigned rows;
    };

    struct Position {
        unsigned col;
        unsigned row;
    };

    explicit FrameBuffer(const Size & size);

    FrameBuffer(const FrameBuffer & other) = default;

    FrameBuffer(FrameBuffer && other) noexcept;

    ~FrameBuffer() = default;

    FrameBuffer & operator=(const FrameBuffer & other) = default;

    FrameBuffer & operator=(FrameBuffer && other) noexcept;

    const Size & size() const { return size_; }

    Color & color_at(Position pos) { return fragment_colors_[index(pos)]; }

    const Color & color_at(Position pos) const { return fragment_colors_[index(pos)]; }

private:
    size_t index(Position pos) const;

    std::vector<Color> fragment_colors_;
    Size size_;
};

inline size_t FrameBuffer::index(Position pos) const {
    return pos.row * size_.cols + pos.col;;
}

#endif //RAY_TRACING_FRAME_BUFFER_H
