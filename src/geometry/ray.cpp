#include "ray.h"

Ray::Ray(const Vec3 & start, const Vec3 & direction)
        : origin_(start),
          direction_(direction) {}
