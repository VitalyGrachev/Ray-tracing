#include "phong_shading_material.h"

#include <cmath>

BRDFunction PhongShadingMaterial::brdf_at(const Vec2 & uv) const {
    const Color diffuse_color = diffuse_color_at(uv);
    const Color specular_color = specular_color_at(uv);
    const float shininess = shininess_at(uv);
    return BRDFunction([=](const Vec3 & v, const Vec3 & l, const Vec3 & n) {
        if (dot(v, n) <= 0.0f || dot(l, n) <= 0.0f) { return Color(0, 0, 0); }

        const float diffuse_intensity = std::clamp(dot(n, l), 0.0f, 1.0f);
        const Vec3 h = (v + l).normalized();
        const float specular_intensity = std::pow(std::clamp(dot(n, h), 0.0f, 1.0f), shininess);
        return diffuse_intensity * diffuse_color + specular_intensity * specular_color;
    });
}
