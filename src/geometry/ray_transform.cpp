#include "ray_transform.h"

Ray transform_ray(const Transform & transform, const Ray & ray) {
    return Ray(transform.transform_point(ray.origin()),
               transform.transform_direction(ray.direction()));
}

Ray untransform_ray(const Transform & transform, const Ray & ray) {
    return Ray(transform.untransform_point(ray.origin()),
               transform.untransform_direction(ray.direction()));
}
