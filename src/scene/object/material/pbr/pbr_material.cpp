#include "pbr_material.h"

#include <cmath>

namespace {

constexpr float pi = 3.14159265359f;

inline float sq(float val) {
    return val * val;
}

Color cook_torrance_specular(const Vec3 & v, const Vec3 & l, const Vec3 & n,
                             const Color & base_reflectivity, float roughness) {
    const Vec3 h = (l + v).normalized();
    const float norm_coef = 0.25f / (Vec3::dotProduct(n, l) * Vec3::dotProduct(n, v));
    return norm_coef * GGX_geometric(v, l, n) * GGX_normal_distribution(h, n, roughness) *
           fresnel_reflectance(base_reflectivity, l, h);
}

Color lambert_diffuse(const Color & diffuse_color) {
    return diffuse_color / pi;
}

Color fresnel_reflectance(const Color & base_reflectivity, const Vec3 & l, const Vec3 & h) {
    return base_reflectivity + (Vec3(1, 1, 1) - base_reflectivity)(1.0f - std::pow(Vec3::dotProduct(l, h), 5.0f));
}

float GGX_normal_distribution(const Vec3 & h, const Vec3 & n, float roughness) {
    const float roughness_2 = sq(roughness);
    return roughness_2 / (pi * sq(sq(Vec3::dotProduct(n, h)) * (roughness_2 - 1) + 1));
}

float GGX_geometric(const Vec3 & v, const Vec3 & l, const Vec3 & n, float roughness) {
    return GGX_g(v, n, roughness) * GGX_g(l, n, roughness);
}

float GGX_g(const Vec3 & e, const Vec3 & n, float roughness) {
    using std::sqrt;
    const float dot = Vec3::dotProduct(e, n);
    return 2.0f * dot / (dot + sqrt(sq(roughness) + sq((1 + roughness) * dot)));
}

}

BRDFunction PBRMaterial::brdf_at(const Vec2 & uv) const {
    const float roughness = roughness_at(uv);
    const Color diffuse_color = diffuse_color_at(uv);
    const Color base_reflectivity = base_reflectivity_at(uv);
    return BRDFunction([=](const Vec3 & v, const Vec3 & l, const Vec3 & n) {
        const Color weights = fresnel_reflectance(base_reflectivity, v, n);
        return cook_torrance_specular(v, l, n, base_reflectivity, roughness) * weights +
               lambert_diffuse(diffuse_color) * (Vec(1, 1, 1) - weights);
    });
}


