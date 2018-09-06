#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

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
    Light(const Color & color, float intensity);

    Light(const Light & other) = default;

    ~Light() = default;

    Light & operator=(const Light & other) = default;

    /**
     * Returns light color
     * @return light color
     */
    const Color & color() const { return color_; }

    /**
     * Returns light intensity in interval [0, 1].
     * @return light intensity
     */
    float intensity() const { return intensity_; }

private:
    Color color_;
    float intensity_;
};

#endif //RAY_TRACING_LIGHT_H
