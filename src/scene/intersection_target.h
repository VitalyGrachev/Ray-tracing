#ifndef RAY_TRACING_INTERSECTION_TARGET_H
#define RAY_TRACING_INTERSECTION_TARGET_H

#include <variant>
#include <optional>
#include "object/object.h"
#include "light/light_source.h"
#include "../geometry/intersection.h"

class IntersectionTarget {
public:
    using ObjectTarget = const Object *;
    using LightSourceTarget = const LightSource *;

    IntersectionTarget(const Intersection & intersection, ObjectTarget target)
            : intersection_(intersection), target_(target) {}

    IntersectionTarget(const Intersection & intersection, LightSourceTarget target)
            : intersection_(intersection), target_(target) {}

    const Intersection & intersection() const { return intersection_; }

    std::optional<ObjectTarget> object_target() const;

    std::optional<LightSourceTarget> light_source_target() const;

private:
    Intersection intersection_;
    std::variant<ObjectTarget, LightSourceTarget> target_;
};

std::optional<IntersectionTarget::ObjectTarget> IntersectionTarget::object_target() const {
    if (auto target_ptr = std::get_if<ObjectTarget>(&target_)) {
        return {*target_ptr};
    }
    return {};
}

std::optional<IntersectionTarget::LightSourceTarget> IntersectionTarget::light_source_target() const {
    if (auto target_ptr = std::get_if<LightSourceTarget>(&target_)) {
        return {*target_ptr};
    }
    return {};
}

#endif //RAY_TRACING_INTERSECTION_TARGET_H
