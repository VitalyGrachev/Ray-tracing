#ifndef RAY_TRACING_SOLID_MATERIAL_H
#define RAY_TRACING_SOLID_MATERIAL_H

#include "pbr_material.h"

class SolidMaterial final : public PBRMaterial {
public:
    ~SolidMaterial() = default;

private:
    Color base_reflectivity_at(const Vec2 & uv) const override { return base_reflectivity_; }

    Color diffuse_color_at(const Vec2 & uv) const override { return diffuse_color_; }

    float roughness_at(const Vec2 & uv) const override { return roughness_; }

    Color base_reflectivity_;
    Color diffuse_color_;
    float roughness_;
};

#endif //RAY_TRACING_SOLID_MATERIAL_H
