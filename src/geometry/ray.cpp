#include "ray.h"

Ray::Ray(const Vec3 & start, const Vec3 & direction)
        : origin_(start),
          direction_(direction) {}

void Ray::set_origin(const Vec3 & origin) {
    origin_ = origin;
}

void Ray::set_direction(const Vec3 & direction) {
    direction_ = direction;
}
