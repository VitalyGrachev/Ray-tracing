#ifndef RAY_TRACING_PHONG_SOLID_MATERIAL_H
#define RAY_TRACING_PHONG_SOLID_MATERIAL_H

#include "phong_shading_material.h"

class PhongSolidMaterial : public PhongShadingMaterial {
public:
    PhongSolidMaterial(const Color & diffuse_color, const Color & specular_color, float shininess)
            : diffuse_color_(diffuse_color),
              specular_color_(specular_color),
              shininess_(shininess) {}

protected:
    Color diffuse_color_at(const Vec2 & tex_coords) const override { return diffuse_color_; }

    Color specular_color_at(const Vec2 & tex_coords) const override { return specular_color_; }

    float shininess_at(const Vec2 & tex_coords) const override { return shininess_; }

private:
    Color diffuse_color_;
    Color specular_color_;
    float shininess_;
};

#endif //RAY_TRACING_PHONG_SOLID_MATERIAL_H
