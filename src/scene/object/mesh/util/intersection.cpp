#include <cmath>
#include "intersection.h"

Intersection::Intersection(const Triangle & triangle,
                           const Vec3 & point,
                           const Vec3 & normal)
        : triangle_(&triangle),
          point_(point),
          normal_(normal) {}

std::optional<Intersection> Intersection::find(const Triangle & triangle, const Ray & ray) {
    const Vec3 normal = triangle_normal(triangle);
    const float cos = Vec3::dotProduct(normal, ray.direction());

    if (!std::isnormal(cos)) { return {}; } // Ray is parallel to triangle's plane

    const Vec3 & A = triangle.points()[0];
    const Vec3 & B = triangle.points()[1];
    const Vec3 & C = triangle.points()[2];
    const float ray_length = -Vec3::dotProduct(normal, ray.start_point() + A) / cos;

    if (ray_length < 0) { return {}; }

    const Vec3 P = ray.start_point() + ray_length * ray.direction();

    const Vec3 AB = B - A;
    const Vec3 AC = C - A;
    const Vec3 PA = P - A;
    Vec3 barycentric = Vec3(AB.x(), AC.x(), PA.x()) * Vec3(AB.y(), AC.y(), PA.y());
    barycentric /= barycentric.z();
    barycentric.setZ(1.0f - barycentric.x() - barycentric.y());

    if (barycentric.x() < 0.0f ||
        barycentric.y() < 0.0f ||
        barycentric.z() < 0.0f) { return {}; } // Intersection point is outside the triangle.

    return std::optional<Intersection>(std::in_place, triangle, P, normal);
}
