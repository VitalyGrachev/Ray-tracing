#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "../../util/transform.h"

class Camera final {
public:
    /**
     * Creates camera with default transform and field of view.
     * Default field of view is 1 radian for horizontal and vertical fields of view.
     */
    explicit Camera(const Transform & transform = Transform());

    Camera(const Camera & other) = default;

    ~Camera() = default;

    Camera & operator=(const Camera & other) = default;

    /**
     * Returns transform, which represent placement of camera in world coordinate system.
     * Camera looks in forward direction.
     * @return transform of the camera
     */
    Transform & transform() { return transform_; }

    const Transform & transform() const { return transform_; }

    /**
     * Returns Vec2 of angles, which define camera's field of view
     * First component contains angle in radians, which define horizontal field of view, in interval (-pi, pi)
     * Second component contains angle in radians, which define vertical field of view, in interval (-pi, pi)
     * @return horizontal and vertical angles, which define camera's field of view
     */
    const Vec2 & field_of_view() const { return fov_; }

    /**
     * Sets horizontal and vertical angles, which define camera's field of view
     * @param fov Vec2, whose first and second components contain horizontal and vertical angles, which define camera's field of view, expressed in radians respectively
     */
    void set_field_of_view(const Vec2 & fov);

private:
    Transform transform_;
    Vec2 fov_;
};

#endif //RAY_TRACING_CAMERA_H
