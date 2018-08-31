#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "../../util/vector.h"

class Ray {
public:
    Ray(const Vec3 & start, const Vec3 & direction);

    Ray(const Ray &) = default;

    ~Ray() = default;

    Ray & operator=(const Ray &) = default;

    const Vec3 & start_point() const;

    const Vec3 & direction() const;

private:
    Vec3 start_;
    Vec3 direction_;
};

#endif //RAY_TRACING_RAY_H
