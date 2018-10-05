#ifndef RAY_TRACING_ILLUMINANCE_H
#define RAY_TRACING_ILLUMINANCE_H

#include "../../geometry/ray.h"
#include "../../util/color.h"

/**
 * Represents illuminance, point on gets by some distant light source
 */
class Illuminance {
public:
    Illuminance(const Ray & direction_to_light_source, const Color & illuminance, float distance_to_source);

    Illuminance(const Illuminance & other) = default;

    ~Illuminance() = default;

    Illuminance & operator=(const Illuminance & other) = default;

    /**
     * @return ray, originated at point of interest directed to light source
     */
    const Ray & ray_to_light_source() const { return direction_to_source_; }

    /**
     * @return distance from point on surface to light source
     */
    float distance_to_source() const { return distance_to_source_; }

    /**
     * @return amount of light travelling from light source, which reaches point of interest
     */
    const Color & illuminane() const { return illuminance_; }

private:
    Ray direction_to_source_;
    Color illuminance_;
    float distance_to_source_;
};

#endif //RAY_TRACING_ILLUMINANCE_H
