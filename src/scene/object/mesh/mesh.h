#ifndef RAY_TRACING_MESH_H
#define RAY_TRACING_MESH_H

#include <optional>
#include <vector>
#include "primitives/triangle.h"
#include "util/intersection.h"

class Mesh {
public:
    std::optional<Intersection> find_intersection(const Ray & ray) const;

private:
    std::vector<Triangle> triangles_;
};

#endif //RAY_TRACING_MESH_H
