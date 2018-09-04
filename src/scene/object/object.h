#ifndef RAY_TRACING_OBJECT_H
#define RAY_TRACING_OBJECT_H

#include <memory>
#include "mesh/mesh.h"
#include "material/material.h"
#include "../../util/transform.h"

class Object {
public:
    Object(const std::shared_ptr<Mesh> & mesh,
           const std::shared_ptr<Material> & material);

    Object(const Object & other) = default;

    ~Object() = default;

    Object & operator=(const Object & other) = default;

    const Transform & transform() const { return transform_; }

    const Mesh & mesh() const { return *mesh_; }

    const Material & material() const { return *material_; }

private:
    Transform transform_;
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<Material> material_;
};


#endif //RAY_TRACING_OBJECT_H
