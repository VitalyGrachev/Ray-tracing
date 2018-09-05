#ifndef RAY_TRACING_INTERSECTION_H
#define RAY_TRACING_INTERSECTION_H

#include "../util/vector.h"

/**
 * Represents intersection point of ray and geometry
 */
class Intersection final {
public:
    Intersection(const Vec3 & point,
                 const Vec3 & normal,
                 const Vec2 & uv);

    Intersection(const Intersection &) = default;

    ~Intersection() = default;

    Intersection & operator=(const Intersection &) = default;

    /**
     * @return point, where intersection occurs
     */
    const Vec3 & point() const { return point_; }

    /**
     * @return normal to geometry surface at intersection point
     */
    const Vec3 & normal() const { return normal_; }

    /**
     * @return texture coordinates at intersection point
     */
    const Vec2 & tex_coords() const { return tex_coords_; }

private:
    Vec3 point_;
    Vec3 normal_;
    Vec2 tex_coords_;
};

#endif //RAY_TRACING_INTERSECTION_H
