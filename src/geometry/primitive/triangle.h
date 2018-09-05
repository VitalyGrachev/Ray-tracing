#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include <array>
#include "../../util/vector.h"
#include "../geometry.h"

/**
 * Represents triangle polygon
 */
class Triangle : public Geometry {
public:
    using Vertices = std::array<Vec3, 3>;

    explicit Triangle(const Vertices & points);

    Triangle(const Vec3 & p1, const Vec3 & p2, const Vec3 & p3);

    Triangle(const Triangle & other) = default;

    ~Triangle() = default;

    Triangle & operator=(const Triangle & other) = default;

    /**
     * @return normal to this triangle's surface
     */
    Vec3 normal() const;

    /**
     * @return vertices, which form this triangle
     */
    const Vertices & vertices() const { return points_; }

    /**
     * Finds point, where ray intersects with this triangle
     * @param ray ray to find intersection with
     * @return std::optional containing found intersection or empty std::optional if there is no intersection
     */
    std::optional<Intersection> find_intersection(const Ray & ray) const override;

private:
    Vertices points_;
};

#endif //RAY_TRACING_TRIANGLE_H
