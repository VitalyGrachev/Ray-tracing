#ifndef RAY_TRACING_PBR_MATERIAL_H
#define RAY_TRACING_PBR_MATERIAL_H

#include "../material.h"

class PBRMaterial : public Material {
public:
    virtual ~PBRMaterial() = default;

    BRDFunction brdf_at(const Vec2 & uv) const override;

protected:
    virtual float roughness_at(const Vec2 & uv) const = 0;

    virtual Color diffuse_color_at(const Vec2 & uv) const = 0;

    virtual Color base_reflectivity_at(const Vec2 & uv) const = 0;
};


#endif //RAY_TRACING_PBR_MATERIAL_H
