#ifndef RAY_TRANSFORM_H
#define RAY_TRANSFORM_H

#include "ray.h"
#include "../util/transform.h"

Ray transform_ray(const Transform & transform, const Ray & ray);

Ray untransform_ray(const Transform & transform, const Ray & ray);

#endif //RAY_TRANSFORM_H
