#ifndef RAY_TRACING_INTERSECTION_TARGET_H
#define RAY_TRACING_INTERSECTION_TARGET_H

#include <variant>
#include "object/object.h"
#include "light/light_source.h"
#include "../geometry/intersection.h"

struct IntersectionTarget {
    using ObjectTarget = Object *;
    using LightSourceTarget = LightSource *;

    Intersection intersection;
    std::variant<ObjectTarget, LightSourceTarget> target;
};

#endif //RAY_TRACING_INTERSECTION_TARGET_H
