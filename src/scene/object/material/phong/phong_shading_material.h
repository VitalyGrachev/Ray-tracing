#ifndef RAY_TRACING_PHONG_SHADING_MATERIAL_H
#define RAY_TRACING_PHONG_SHADING_MATERIAL_H

#include "../material.h"

class PhongShadingMaterial : public Material {
public:
    BRDFunction brdf_at(const Vec2 & uv) const override;

protected:
    virtual Color diffuse_color_at(const Vec2 & tex_coords) const = 0;
    virtual Color specular_color_at(const Vec2 & tex_coords) const = 0;
    virtual float shininess_at(const Vec2 & tex_coords) const = 0;
};

#endif //RAY_TRACING_PHONG_SHADING_MATERIAL_H
