#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "../../../util/color.h"

/**
 * Interface. Represents optical properties of object
 */
class Material {
public:
    virtual ~Material() = default;

    virtual Color color_at(const Vec2 & tex_coords) const = 0;

    virtual Vec3 diffuse_reflectance_at(const Vec2 & tex_coords) const = 0;

    virtual Vec3 specular_reflectance_at(const Vec2 & tex_coords) const = 0;

    virtual Vec3 specular_power_at(const Vec2 & tex_coords) const = 0;

    virtual float refractive_index_at(const Vec2 & tex_coords) const = 0;

    virtual float shininess_at(const Vec2 & tex_coords) const = 0;
};

#endif //RAY_TRACING_MATERIAL_H
