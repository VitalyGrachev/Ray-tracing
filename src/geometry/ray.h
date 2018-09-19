#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "../util/vector.h"

/**
 * Represents a ray emitted from origin in given direction
 */
class Ray {
public:
    Ray(const Vec3 & start, const Vec3 & direction);

    Ray(const Ray &) = default;

    ~Ray() = default;

    Ray & operator=(const Ray &) = default;

    /**
     * @return start point of the ray
     */
    const Vec3 & origin() const { return origin_; }

    /**
     * @return direction the ray is emitted in
     */
    const Vec3 & direction() const { return direction_; }

    /**
     * Sets new origin for the ray
     * @param origin new origin
     */
    void set_origin(const Vec3 & origin);

    /**
     * Sets new direction for the ray
     * @param direction new direction
     */
    void set_direction(const Vec3 & direction);

private:
    Vec3 origin_;
    Vec3 direction_;
};

#endif //RAY_TRACING_RAY_H
