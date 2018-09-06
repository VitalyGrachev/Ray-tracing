#include <cmath>
#include "triangle.h"

Triangle::Triangle(const Triangle::Vertices & points) {
    std::copy(points.begin(), points.end(), points_.begin());
}

Triangle::Triangle(const Vec3 & p1, const Vec3 & p2, const Vec3 & p3) {
    points_[0] = p1;
    points_[1] = p2;
    points_[2] = p3;
}

std::optional<Intersection> Triangle::find_intersection(const Ray & ray) const {
    const Vec3 normal = this->normal();
    const float cos = QVector3D::dotProduct(normal, ray.direction());

    if (!std::isnormal(cos)) { return {}; } // Ray is parallel to triangle's plane

    const Vec3 & A = this->vertices()[0];
    const Vec3 & B = this->vertices()[1];
    const Vec3 & C = this->vertices()[2];
    const float ray_length = -QVector3D::dotProduct(normal, ray.origin() + A) / cos;

    if (ray_length < 0) { return {}; }

    const Vec3 P = ray.origin() + ray_length * ray.direction();

    const Vec3 AB = B - A;
    const Vec3 AC = C - A;
    const Vec3 PA = P - A;
    Vec3 barycentric = Vec3(AB.x(), AC.x(), PA.x()) * Vec3(AB.y(), AC.y(), PA.y());
    barycentric /= barycentric.z();
    barycentric.setZ(1.0f - barycentric.x() - barycentric.y());

    if (barycentric.x() < 0.0f ||
        barycentric.y() < 0.0f ||
        barycentric.z() < 0.0f) { return {}; } // Intersection point is outside the triangle.

    return std::optional<Intersection>(std::in_place, P, normal, Vec2(0, 0));
}

Vec3 Triangle::normal() const {
    const Vertices & vertices = this->vertices();
    const Vec3 AB = vertices[1] - vertices[0];
    const Vec3 AC = vertices[2] - vertices[0];
    return (AB * AC).normalized();
}
