#ifndef RAY_TRACING_LIGHT_SOURCE_H
#define RAY_TRACING_LIGHT_SOURCE_H

#include "light.h"
#include "../../geometry/geometry.h"

/**
 * Piece of geometry that emit light
 */
class LightSource {
public:
    /**
     * @return Light emitted by light source
     */
    const Light & light() const;

    /**
     * @return visible geometry of light source
     */
    const Geometry & geometry() const;
};

#endif //RAY_TRACING_LIGHT_SOURCE_H
