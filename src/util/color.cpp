#include "color.h"

Color::Color(const Vec3 & vec) : components_(vec) {}

Color::Color(float red, float green, float blue) : components_(red, green, blue) {}

Color & Color::operator+=(const Color & rhs) {
    components_ += rhs.components_;
    return *this;
}

Color & Color::operator-=(const Color & rhs) {
    components_ -= rhs.components_;
    return *this;
}

Color & Color::operator*=(const Color & rhs) {
    components_ *= rhs.components_;
    return *this;
}

Color & Color::operator*=(const Vec3 & rhs) {
    components_ *= rhs;
    return *this;
}

Color & Color::operator*=(float factor) {
    components_ *= factor;
    return *this;
}

Color & Color::operator/=(float factor) {
    components_ /= factor;
    return *this;
}

Color operator+(const Color & lhs, const Color & rhs) {
    Color result(lhs);
    result += rhs;
    return result;
}

Color operator-(const Color & lhs, const Color & rhs) {
    Color result(lhs);
    result -= rhs;
    return result;
}

Color operator*(const Color & lhs, const Color & rhs) {
    Color result(lhs);
    result *= rhs;
    return result;
}

Color operator*(const Color & color, const Vec3 & vector) {
    Color result(color);
    result *= vector;
    return result;
}

Color operator*(const Vec3 & vector, const Color & color) {
    return color * vector;
}

Color operator*(const Color & color, float factor) {
    Color result(color);
    result *= factor;
    return result;
}

Color operator*(float factor, const Color & color) {
    return color * factor;
}

Color operator/(const Color & color, float factor) {
    Color result(color);
    result /= factor;
    return result;
}