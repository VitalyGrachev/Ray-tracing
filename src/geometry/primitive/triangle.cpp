#include "triangle.h"

Vec3 triangle_normal(const Triangle & tr) {
    const Vec3 ab = tr.points()[1] - tr.points()[0];
    const Vec3 ac = tr.points()[2] - tr.points()[0];
    return (ab * ac).normalized();
}

Triangle::Triangle(const Triangle::Points & points) {
    std::copy(points.begin(), points.end(), points_.begin());
}

Triangle::Triangle(const Vec3 & p1, const Vec3 & p2, const Vec3 & p3) {
    points_[0] = p1;
    points_[1] = p2;
    points_[2] = p3;
}
