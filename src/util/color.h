#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H

#include "vector.h"

/**
 * Represents RGB color in extended precision
 */
class Color {
public:
    explicit Color(const Vec3 & vec);

    Color(float red, float green, float blue);

    Color(const Color & other) = default;

    ~Color() = default;

    Color & operator=(const Color & other) = default;

    /**
     * @return red component of color
     */
    float & r() { return components_[0]; }

    float r() const { return components_[0]; }

    /**
     * @return green component of color
     */
    float & g() { return components_[1]; }

    float g() const { return components_[1]; }

    /**
     * @return blue component of color
     */
    float & b() { return components_[2]; }

    float b() const { return components_[2]; }

    /**
     * Adds to the components of this color corresponding components of rhs
     */
    Color & operator+=(const Color & rhs);

    /**
     * Subtracts from the components of this color corresponding components of rhs
     */
    Color & operator-=(const Color & rhs);

    /**
     * Multiplies the components of this color by the corresponding components of rhs
     */
    Color & operator*=(const Color & rhs);

    /**
     * Multiplies the components of this color by the corresponding components of rhs
     */
    Color & operator*=(const Vec3 & rhs);

    /**
     * Multiplies the components of this color by given factor
     */
    Color & operator*=(float factor);

    /**
     * Divides the components of this color by given factor
     */
    Color & operator/=(float factor);

    bool operator==(const Color & rhs) const { return components_ == rhs.components_; }

    bool operator!=(const Color & rhs) const { return components_ != rhs.components_; }

private:
    Vec3 components_;
};

Color operator+(const Color & lhs, const Color & rhs);

Color operator-(const Color & lhs, const Color & rhs);

Color operator*(const Color & lhs, const Color & rhs);

Color operator*(const Vec3 & vector, const Color & color);

Color operator*(const Color & color, const Vec3 & vector);

Color operator*(const Color & color, float factor);

Color operator*(float factor, const Color & color);

Color operator/(const Color & color, float factor);

#endif //RAY_TRACING_COLOR_H
