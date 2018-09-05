#ifndef RAY_TRACING_GEOMETRY_H
#define RAY_TRACING_GEOMETRY_H

#include <optional>
#include "intersection.h"
#include "ray.h"

/**
 * Interface. Represents piece of geometry, which ray can intersect with
 */
class Geometry {
public:
    virtual ~Geometry() = default;

    /**
     * Finds closest to ray origin point, where ray intersects with this geometry
     * @param ray
     * @return std::optional containing found intersection or empty std::optional if there is no intersection
     */
    virtual std::optional<Intersection> find_intersection(const Ray & ray) const = 0;
};

#endif //RAY_TRACING_GEOMETRY_H
