#ifndef RAY_TRACING_SOLID_MATERIAL_H
#define RAY_TRACING_SOLID_MATERIAL_H

#include "pbr_material.h"

/**
 * PBRMaterial, which has the same optical properties at every point of it's surface
 */
class PBRSolidMaterial final : public PBRMaterial {
public:
    /**
     * Creates PBRSolidMaterial with given optical properties
     */
    PBRSolidMaterial(const Color & diffuse_color, const Color & base_reflectivity, float roughness)
            : base_reflectivity_(base_reflectivity), diffuse_color_(diffuse_color), roughness_(roughness) {}

    ~PBRSolidMaterial() = default;

private:
    Color base_reflectivity_at(const Vec2 & uv) const override { return base_reflectivity_; }

    Color diffuse_color_at(const Vec2 & uv) const override { return diffuse_color_; }

    float roughness_at(const Vec2 & uv) const override { return roughness_; }

    Color base_reflectivity_;
    Color diffuse_color_;
    float roughness_;
};

#endif //RAY_TRACING_SOLID_MATERIAL_H
