#ifndef RAY_TRACING_MESH_H
#define RAY_TRACING_MESH_H

#include <vector>
#include "primitives/triangle.h"
#include "../../../util/enumeration.h"

class Mesh {
public:
    using TriangleIterator = std::vector<Triangle>::const_iterator;

    Enumeration<TriangleIterator> enumerate_triangles() const;

private:
    std::vector<Triangle> triangles_;
};

#endif //RAY_TRACING_MESH_H
