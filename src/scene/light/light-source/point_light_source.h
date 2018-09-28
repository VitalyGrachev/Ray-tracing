#ifndef RAY_TRACING_POINT_LIGHT_SOURCE_H
#define RAY_TRACING_POINT_LIGHT_SOURCE_H

#include "../light_source.h"
#include "../../../util/transform.h"

class PointLightSource : public LightSource {
public:
    PointLightSource(const Color & light_color, float attenuation, const Transform & transform = Transform());

    Transform & transform() { return transform_; }

    const Transform & transform() const { return transform_; }

    Illuminance illuminate_point(const Vec3 & point) const override;

private:
    Vec3 attenuation(float distance) const;

    Transform transform_;
    Color light_color_;
    float attenuation_;
};

#endif //RAY_TRACING_POINT_LIGHT_SOURCE_H
