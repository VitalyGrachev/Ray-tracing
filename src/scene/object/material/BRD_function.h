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
    explicit BRDFunction(F && f)
            : internal_(std::move(f)) {}

    BRDFunction(const BRDFunction & other) = default;

    BRDFunction(BRDFunction && other) = default;

    ~BRDFunction() = default;

    BRDFunction & operator=(const BRDFunction & other) = default;

    BRDFunction & operator=(BRDFunction && other) = default;

    /**
     * Returns amount of light reflected in view_direction by surface with given normal when lit by light from light_direction
     * @param view_direction direction of interest
     * @param light_direction direction opposite to direction of incident light
     * @param normal_direction normal to surface
     * @return amount of light reflected in view_direction
     */
    Color operator()(const Vec3 & view_direction,
                     const Vec3 & light_direction,
                     const Vec3 & normal_direction) const {
        return internal_(view_direction, light_direction, normal_direction);
    }

private:
    std::function<Color(const Vec3 &, const Vec3 &, const Vec3 &)> internal_;
};

#endif //RAY_TRACING_BRD_FUNCTION_H
