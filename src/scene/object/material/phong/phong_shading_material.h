#ifndef RAY_TRACING_PHONG_SHADING_MATERIAL_H
#define RAY_TRACING_PHONG_SHADING_MATERIAL_H

#include "../material.h"

/**
 * Represents material with optical properties defined by Phong shading model
 */
class PhongShadingMaterial : public Material {
public:

    /**
     * Returns bidirectional reflectance distribution function at given point
     * @param uv point on surface
     * @return bidirectional reflectance distribution function
     */
    BRDFunction brdf_at(const Vec2 & uv) const override;

protected:
    virtual Color diffuse_color_at(const Vec2 & tex_coords) const = 0;
    virtual Color specular_color_at(const Vec2 & tex_coords) const = 0;
    virtual float shininess_at(const Vec2 & tex_coords) const = 0;
};

#endif //RAY_TRACING_PHONG_SHADING_MATERIAL_H
