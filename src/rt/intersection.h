#ifndef RAY_TRACING_INTERSECTION_H
#define RAY_TRACING_INTERSECTION_H

#include "../scene/object/mesh/primitives/triangle.h"
#include "../util/vector.h"
#include "ray.h"

class Intersection {
public:
    static std::optional<Intersection> find(const Triangle & triangle, const Ray & ray);

    Intersection(const Triangle & triangle, const Vec3 & point, const Vec3 & normal);

    Intersection(const Intersection &) = default;

    ~Intersection() = default;

    Intersection & operator=(const Intersection &) = default;

    const Vec3 & point() const { return point_; }

    const Vec3 & normal() const { return normal_; }

    const Triangle & triangle() const { return *triangle_; }

private:
    const Triangle * triangle_;
    Vec3 point_;
    Vec3 normal_;
};

#endif //RAY_TRACING_INTERSECTION_H
