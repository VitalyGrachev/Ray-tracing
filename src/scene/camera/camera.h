#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "../../util/transform.h"

class Camera {
public:
    const Transform & transform() const { return transform_; }

private:
    Transform transform_;
};

#endif //RAY_TRACING_CAMERA_H
