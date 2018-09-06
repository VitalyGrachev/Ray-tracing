#include "camera.h"

Camera::Camera()
        : fov_(Vec2(1, 1)) {}

void Camera::set_field_of_view(const Vec2 & fov) {
    fov_ = fov;
}
