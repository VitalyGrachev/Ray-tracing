#include "triangle.h"

#include <cmath>

namespace {

/**
 * Checks whether a and b have the same sign.
 * Zero has same sign only with zero.
 * @return true if signs on a and b are the same, false otherwise
 */
inline bool same_sign(float a, float b) {
    return a * b > 0.0f;
}

}

Triangle::Triangle(const Triangle::Vertices & points) {
    std::copy(points.begin(), points.end(), points_.begin());
}

Triangle::Triangle(const Vec3 & p1, const Vec3 & p2, const Vec3 & p3) {
    points_[0] = p1;
    points_[1] = p2;
    points_[2] = p3;
}

std::optional<Intersection> Triangle::find_intersection(const Ray & ray) const {
    const Vec3 n = normal();
    const Vec3 & A = points_[0];
    const Vec3 & B = points_[1];
    const Vec3 & C = points_[2];

    const float signed_dist_to_plane = dot(A - ray.origin(), n);
    const float cos_n_dir = dot(ray.direction(), n);
    if (!same_sign(cos_n_dir, signed_dist_to_plane)) { return std::nullopt; } // triangle is behind the ray origin

    const Vec3 P = ray.origin() + (signed_dist_to_plane / cos_n_dir) * ray.direction();

    const Vec3 AB = B - A;
    const Vec3 BC = C - B;
    const Vec3 CA = A - C;
    const Vec3 AP = P - A;
    const Vec3 BP = P - B;
    const Vec3 CP = P - C;

    if (dot(cross(AB, AP), n) < 0.0f) { return std::nullopt; } // P is outside the triangle

    if (dot(cross(BC, BP), n) < 0.0f) { return std::nullopt; } // P is outside the triangle

    if (dot(cross(CA, CP), n) < 0.0f) { return std::nullopt; } // P is outside the triangle

    return std::make_optional<Intersection>(P, n, Vec2(0, 0));
}

Vec3 Triangle::normal() const {
    const Vertices & v = points_;
    const Vec3 & A = v[0];
    const Vec3 & B = v[1];
    const Vec3 & C = v[2];
    const Vec3 AB = B - A;
    const Vec3 AC = C - A;
    return cross(AB, AC).normalized();
}
