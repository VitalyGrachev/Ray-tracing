#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include <array>
#include "../../util/vector.h"

class Triangle {
public:
    using Points = std::array<Vec3, 3>;

    explicit Triangle(const Points & points);

    Triangle(const Vec3 & p1, const Vec3 & p2, const Vec3 & p3);

    Triangle(const Triangle & other) = default;

    ~Triangle() = default;

    Triangle & operator=(const Triangle & other) = default;

    const Points & points() const { return points_; }

private:
    Points points_;
};

Vec3 triangle_normal(const Triangle & tr);

#endif //RAY_TRACING_TRIANGLE_H
