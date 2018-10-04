#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "../geometry.h"

/**
 * Represents spherical primitive
 */
class Sphere : public Geometry {
public:
    /**
     * Creates new sphere with radius 1
     */
    Sphere() = default;

    Sphere(const Sphere & other) = default;

    ~Sphere() = default;

    Sphere & operator=(const Sphere & other) = default;

    /**
     * Finds point, where ray intersects with sphere
     * @param ray ray to find intersection with
     * @return std::optional containing found intersection or empty std::optional if there is no intersection
     */
    std::optional<Intersection> find_intersection(const Ray & ray) const override;

private:
    Vec2 tex_coords(const Vec3 & point) const;

    static const float sq_radius_;
};

#endif //RAY_TRACING_SPHERE_H
