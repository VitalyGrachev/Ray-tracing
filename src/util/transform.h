#ifndef RAY_TRACING_TRANSFORM_H
#define RAY_TRACING_TRANSFORM_H

#include "vector.h"

/**
 * Describes elements position, rotation and scale in world coordinate system
 */
class Transform {
public:
    Transform();

    Transform(const Transform & other);

    ~Transform();

    Transform & operator=(const Transform & other);

    Transform & translate(const Vec3 & vector);

    Transform & rotate(float angles, const Vec3 & axis);

    Transform & scale(const Vec3 & factors);

    Vec3 map_to_world(const Vec3 & local) const;

    Vec3 map_to_local(const Vec3 & world) const;
};

#endif //RAY_TRACING_TRANSFORM_H
