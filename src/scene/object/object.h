#ifndef RAY_TRACING_OBJECT_H
#define RAY_TRACING_OBJECT_H

#include "mesh/mesh.h"

class Object {
public:
    std::optional<Intersection> find_intersection(const Ray & ray) const;
private:
    Mesh mesh_;
};


#endif //RAY_TRACING_OBJECT_H
