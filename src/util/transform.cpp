#include "transform.h"

namespace {

constexpr float pi = 3.14159265358979323846f;

constexpr Vec3 zero = Vec3(0.0f, 0.0f, 0.0f);
constexpr Vec3 local_forward = Vec3(1.0f, 0.0f, 0.0f);
constexpr Vec3 local_left = Vec3(0.0f, 1.0f, 0.0f);
constexpr Vec3 local_up = Vec3(0.0f, 0.0f, 1.0f);

float radians_to_degrees(float radians) {
    return radians / pi * 180.0f;
}

float degrees_to_radians(float degrees) {
    return degrees / 180.0f * pi;
}

}

Transform Transform::indentity() {
    return Transform();
}

Transform::Transform() {}

Transform & Transform::translate(const Vec3 & vector) {
    forward_transform_matrix_.translate(vector);
    recalculate_backward_transform();
    return *this;
}

Transform & Transform::rotate(float angle, const Vec3 & axis) {
    forward_transform_matrix_.rotate(radians_to_degrees(angle), axis);
    recalculate_backward_transform();
    return *this;
}

Transform & Transform::scale(const Vec3 & factors) {
    forward_transform_matrix_.scale(factors);
    recalculate_backward_transform();
    return *this;
}

Transform & Transform::scale(float factor) {
    forward_transform_matrix_.scale(factor);
    recalculate_backward_transform();
    return *this;
}

Vec3 Transform::origin() const {
    return transform_point(zero);
}

Vec3 Transform::forward() const {
    return transform_direction(local_forward);
}

Vec3 Transform::left() const {
    return transform_direction(local_left);
}

Vec3 Transform::up() const {
    return transform_direction(local_up);
}

Vec3 Transform::transform_point(const Vec3 & point) const {
    return forward_transform_matrix_.map(point);
}

Vec3 Transform::untransform_point(const Vec3 & point) const {
    return backward_transform_matrix_.map(point);
}

Vec3 Transform::transform_direction(const Vec3 & direction) const {
    return forward_transform_matrix_.mapVector(direction);
}

Vec3 Transform::untransform_direction(const Vec3 & direction) const {
    return backward_transform_matrix_.mapVector(direction);
}

void Transform::recalculate_backward_transform() {
    backward_transform_matrix_ = forward_transform_matrix_.inverted();
}
