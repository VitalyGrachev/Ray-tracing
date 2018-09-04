#ifndef RAY_TRACING_OBJECT_H
#define RAY_TRACING_OBJECT_H

#include <memory>
#include "mesh/mesh.h"
#include "material/material.h"

class Object {
public:
    const Mesh & mesh() const { return *mesh_; }

    const Material & material() const { return *material_; }

private:
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<Material> material_;
};


#endif //RAY_TRACING_OBJECT_H
