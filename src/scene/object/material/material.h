#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "BRD_function.h"

/**
 * Interface. Represents optical properties of object
 */
class Material {
public:
    virtual ~Material() = default;

    /**
     * Returns bidirectional reflectance distribution function at given point
     * @param uv point on surface
     * @return bidirectional reflectance distribution function
     */
    virtual BRDFunction brdf_at(const Vec2 & uv) const = 0;
};

#endif //RAY_TRACING_MATERIAL_H
