#ifndef RAY_TRACING_MESH_H
#define RAY_TRACING_MESH_H

#include <vector>
#include "../primitive/triangle.h"
#include "../../util/enumeration.h"

class Mesh : public Geometry {
public:
    using TriangleIterator = std::vector<Triangle>::const_iterator;

    explicit Mesh(const std::vector<Triangle> & triangles);

    explicit Mesh(std::vector<Triangle> && triangles);

    Enumeration<TriangleIterator> enumerate_triangles() const;

    std::optional<Intersection> find_intersection(const Ray & ray) const override;

private:
    std::vector<Triangle> triangles_;
};

#endif //RAY_TRACING_MESH_H
