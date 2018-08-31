#include "ray.h"

Ray::Ray(const Vec3 & start, const Vec3 & direction)
        : start_(start),
          direction_(direction) {}
