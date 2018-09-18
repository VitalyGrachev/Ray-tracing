#ifndef RAY_TRACING_BRD_FUNCTION_H
#define RAY_TRACING_BRD_FUNCTION_H

#include <functional>
#include "../../../util/vector.h"
#include "../../../util/color.h"

/**
 * Represents Bidirectional Reflectance Distribution Function
 */
class BRDFunction {
public:
    template<class F>
    explicit BRDFunction(F && f);

    BRDFunction(const BRDFunction & other) = default;

    BRDFunction(BRDFunction && other) = default;

    ~BRDFunction() = default;

    BRDFunction & operator=(const BRDFunction & other) = default;

    BRDFunction & operator=(BRDFunction && other) = default;

    Color operator()(const Vec3 & view_direction,
                     const Vec3 & light_direction,
                     const Vec3 & normal_direction) const;

private:
    std::function<Color(const Vec3 &, const Vec3 &, const Vec3 &)> internal_;
};

template<class F>
BRDFunction::BRDFunction(F && f)
        : internal_(std::forward(f)) {}

Color
BRDFunction::operator()(const Vec3 & view_direction,
                        const Vec3 & light_direction,
                        const Vec3 & normal_direction) const {
    return internal_(view_direction, light_direction, normal_direction);
}

#endif //RAY_TRACING_BRD_FUNCTION_H
