#ifndef RAY_TRACING_INTERSECTION_TARGET_H
#define RAY_TRACING_INTERSECTION_TARGET_H

#include <functional>

#include "object/object.h"
#include "../geometry/intersection.h"

/**
 * Stores intersected object and intersection point
 */
class IntersectionTarget {
public:
    /**
     * Creates IntersectionTarget for given target and intersection
     * @param intersection intersection info
     * @param target intersected object
     */
    IntersectionTarget(const Intersection & intersection, const Object & target)
            : intersection_(intersection),
              target_(std::ref(target)) {}

    IntersectionTarget(const IntersectionTarget & other) = default;

    ~IntersectionTarget() = default;

    IntersectionTarget & operator=(const IntersectionTarget & other) = default;

    /**
     * @return intersection info
     */
    const Intersection & intersection() const { return intersection_; }

    /**
     * @return object which was intersected by ray
     */
    const Object & target() const { return target_; }

private:
    Intersection intersection_;
    std::reference_wrapper<const Object> target_;
};

#endif //RAY_TRACING_INTERSECTION_TARGET_H
