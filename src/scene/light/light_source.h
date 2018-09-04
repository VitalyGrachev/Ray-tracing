#ifndef RAY_TRACING_LIGHT_SOURCE_H
#define RAY_TRACING_LIGHT_SOURCE_H

#include "light.h"
#include "../object/mesh/mesh.h"

/**
 * Piece of geometry that emit light
 */
class LightSource {
public:
    const Light & light() const;
    const Mesh & mesh() const;
};

#endif //RAY_TRACING_LIGHT_SOURCE_H
