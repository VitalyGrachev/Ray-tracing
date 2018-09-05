#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include "../../util/vector.h"

class Light {
public:
    const Vec3 & color() const;
    float intensity() const;
};

#endif //RAY_TRACING_LIGHT_H
