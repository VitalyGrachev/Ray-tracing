#ifndef RAY_TRACING_FRAGMENT_H
#define RAY_TRACING_FRAGMENT_H

#include "../../util/color.h"

class Fragment {
public:
    explicit Fragment(Color & fragment_color) : fragment_color_(fragment_color) {}

    virtual ~Fragment() = default;

    virtual void add_color(const Color & color);

private:
    Color & fragment_color_;
};

void Fragment::add_color(const Color & color) {
    fragment_color_ += color;
}

#endif //RAY_TRACING_FRAGMENT_H
