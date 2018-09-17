#ifndef RAY_TRACING_LIGHT_SOURCE_H
#define RAY_TRACING_LIGHT_SOURCE_H

#include "illuminance.h"

/**
 * Interface. Represents light source, which can illuminate objects
 */
class LightSource {
public:
    virtual ~LightSource() = default;

    /**
     * Returns illuminance of given point by the light source
     * @param point illuminated point
     * @return illuminance of given point
     */
    virtual Illuminance illuminate_point(const Vec3 & point) const = 0;
};

#endif //RAY_TRACING_LIGHT_SOURCE_H
