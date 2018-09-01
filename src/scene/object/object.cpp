#include "object.h"

std::optional<Intersection> Object::find_intersection(const Ray & ray) const {
    return mesh_.find_intersection(ray);
}
