#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include <functional>
#include "../../util/color.h"

/**
 * Represents properties of emitted light
 */
class Light final {
public:
    /**
     * Creates light with given color and intensity
     * @param color light's color
     * @param intensity light's intensity, clamped between 0 and 1
     */

    /**
     * Creates light with given color and attenuation function
     * @param color light color
     * @param attenuation light attenuation callable
     */
    template<class AttF>
    Light(const Color & color, AttF && attenuation);

    Light(const Light & other) = default;

    ~Light() = default;

    Light & operator=(const Light & other) = default;

    /**
     * Returns light color
     * @return light color
     */
    const Color & color() const { return color_; }

    /**
     *
     * @param distance
     * @return
     */
    Vec3 attenuation(float distance) const { return attenuation_(distance); }

private:
    Color color_;
    std::function<Vec3(float)> attenuation_;
};

template<class AttF>
Light::Light(const Color & color, AttF && attenuation)
        : color_(color), attenuation_(attenuation) {}

#endif //RAY_TRACING_LIGHT_H
