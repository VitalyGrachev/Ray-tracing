#ifndef RAY_TRACING_OBJECT_H
#define RAY_TRACING_OBJECT_H

#include <memory>
#include "material/material.h"
#include "../../geometry/geometry.h"
#include "../../util/transform.h"

/**
 * Represents single visible object on scene
 */
class Object final {
public:
    Object(const std::shared_ptr<Geometry> & geometry,
           const std::shared_ptr<Material> & material);

    Object(const Object & other) = default;

    ~Object() = default;

    Object & operator=(const Object & other) = default;

    /**
     * @return transform, which represent placement of object in world coordinate system
     */
    Transform & transform() { return transform_; }

    /**
     * @return transform, which represent placement of object in world coordinate system
     */
    const Transform & transform() const { return transform_; }

    /**
     * @return geometry of object defined in local coordinate system
     */
    const Geometry & geometry() const { return *geometry_; }

    /**
     * @return material object has
     */
    const Material & material() const { return *material_; }

private:
    Transform transform_;
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Material> material_;
};


#endif //RAY_TRACING_OBJECT_H
