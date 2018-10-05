#ifndef RAY_TRACING_MESH_H
#define RAY_TRACING_MESH_H

#include <vector>
#include "../primitive/triangle.h"
#include "../../util/enumeration.h"

/**
 * Represents compound geometry, which consists of triangles
 */
class Mesh : public Geometry {
public:
    using TriangleIterator = std::vector<Triangle>::const_iterator;

    /**
     * Creates mesh consisting of given triangles
     */
    explicit Mesh(const std::vector<Triangle> & triangles);

    /**
     * Creates mesh consisting of given triangles
     */
    explicit Mesh(std::vector<Triangle> && triangles);

    /**
     * @return enumeration of triangles that make up the mesh
     */
    Enumeration<TriangleIterator> enumerate_triangles() const;

    /**
     * Finds point, where ray intersects with the mesh
     * @param ray ray to find intersection with
     * @return std::optional containing found intersection or empty std::optional if there is no intersection
     */
    std::optional<Intersection> find_intersection(const Ray & ray) const override;

private:
    std::vector<Triangle> triangles_;
};

#endif //RAY_TRACING_MESH_H
