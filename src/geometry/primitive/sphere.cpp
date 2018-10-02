#include "sphere.h"

#include <cmath>

Sphere::Sphere(float radius) : radius_(radius) {}

std::optional<Intersection> Sphere::find_intersection(const Ray & ray) const {
    // (d * d)t^2 + 2(d * o)t + (o * o) - r^2 = 0
    // a * t^2 + 2*b * t + c = 0
    const float a = Vec3::dotProduct(ray.direction(), ray.direction());
    const float b = Vec3::dotProduct(ray.direction(), ray.origin());
    const float c = Vec3::dotProduct(ray.origin(), ray.origin()) - radius_ * radius_;

    const float discriminant = b * b - a * c;
    if (discriminant < 0) { return std::nullopt; } // No intersection

    float t;
    switch (std::fpclassify(discriminant)) {
        case FP_ZERO:
            t = -b / a;
            break;
        case FP_NORMAL:
            t = (-b - std::sqrt(discriminant)) / a;
            if (t < 0) { // Line intersects sphere behind ray origin
                t = (-b + std::sqrt(discriminant)) / a;
            }
            break;
        default:
            return std::nullopt;
    }
    return from_t(ray, t);
}

std::optional<Intersection> Sphere::from_t(const Ray & ray, float t) const {
    if (t < 0) { return std::nullopt; } // Line intersects sphere behind ray origin
    const Vec3 point = ray.origin() + t * ray.direction();
    const Vec3 normal = point.normalized();
    return std::make_optional<Intersection>(point, normal, tex_coords(point));
}

Vec2 Sphere::tex_coords(const Vec3 & point) const {
    return Vec2(0, 0);
}
