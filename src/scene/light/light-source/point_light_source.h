#ifndef RAY_TRACING_POINT_LIGHT_SOURCE_H
#define RAY_TRACING_POINT_LIGHT_SOURCE_H

#include "../light_source.h"
#include "../../../util/transform.h"

/**
 * Represents point light source
 */
class PointLightSource : public LightSource {
public:
    /**
     * Creates point light source with given properties
     * @param light_color color of light emitted by the light source
     * @param attenuation factor of light attenuation
     * @param transform placement of the light source in world coordinate system
     */
    PointLightSource(const Color & light_color, float attenuation, const Transform & transform = Transform());

    /**
     * @return placement of the light source in world coordinate system
     */
    Transform & transform() { return transform_; }

    /**
     * @return placement of the light source in world coordinate system
     */
    const Transform & transform() const { return transform_; }

    /**
     * Returns illuminance of given point by the light source
     * @param point illuminated point
     * @return illuminance of given point by the light source
     */
    Illuminance illuminate_point(const Vec3 & point) const override;

private:
    Vec3 attenuation(float distance) const;

    Transform transform_;
    Color light_color_;
    float attenuation_;
};

#endif //RAY_TRACING_POINT_LIGHT_SOURCE_H
