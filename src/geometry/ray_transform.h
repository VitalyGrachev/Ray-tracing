#ifndef RAY_TRANSFORM_H
#define RAY_TRANSFORM_H

#include "ray.h"
#include "../util/transform.h"

/**
 * Applies given transform to given ray
 * @param transform transform to apply
 * @param ray ray to transform
 * @return transformed ray
 */
Ray transform_ray(const Transform & transform, const Ray & ray);

/**
 * Applies backward transform defined by given transform to given ray
 * @param transform transform used for transformation
 * @param ray ray to transform
 * @return backward transformed ray
 */
Ray untransform_ray(const Transform & transform, const Ray & ray);

#endif //RAY_TRANSFORM_H
