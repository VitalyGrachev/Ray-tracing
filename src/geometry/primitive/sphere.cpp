#include "sphere.h"

#include <cmath>

const float Sphere::sq_radius_ = 0.5f * 0.5f;

std::optional<Intersection> Sphere::find_intersection(const Ray & ray) const {
    const Vec3 to_center = -ray.origin();
    const float proj_len = dot(to_center, ray.direction());
    if (proj_len <= 0.0f) { return std::nullopt; } // sphere is behind the ray origin

    const Vec3 projection = proj_len * ray.direction();
    const float sq_dist_from_center_to_ray = (ray.origin() + projection).lengthSquared();
    if(sq_dist_from_center_to_ray > sq_radius_) { return std::nullopt; } // no intersection

    const Vec3 point = ray.origin() + projection - std::sqrt(sq_radius_ - sq_dist_from_center_to_ray) * ray.direction();
    return std::make_optional<Intersection>(point, point.normalized(), tex_coords(point));
}

Vec2 Sphere::tex_coords(const Vec3 & point) const {
    return Vec2(0, 0);
}
