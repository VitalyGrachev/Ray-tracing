#include "point_light_source.h"

PointLightSource::PointLightSource(const Color & light_color,
                                   float attenuation,
                                   const Transform & transform)
        : transform_(transform), light_color_(light_color), attenuation_(attenuation) {}

Illuminance PointLightSource::illuminate_point(const Vec3 & point) const {
    const Vec3 direction = transform_.origin() - point;
    const float distance = direction.length();
    const Vec3 att = attenuation(distance);
    return Illuminance(Ray(point, direction), att * light_color_, distance);
}

Vec3 PointLightSource::attenuation(float distance) const {
    const float att = 1.0f / (attenuation_ * distance * distance);
    return Vec3(att, att, att);
}
