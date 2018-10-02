#ifndef RAY_TRACING_TRANSFORM_H
#define RAY_TRACING_TRANSFORM_H

#include "vector.h"
#include "matrix.h"

/**
 * Describes elements position, rotation and scale in world coordinate system
 */
class Transform {
public:
    /**
     * @return identity transform, which does nothing
     */
    static Transform indentity();

    /**
     * Creates identity transform, which does nothing
     */
    Transform();

    Transform(const Transform & other) = default;

    ~Transform() = default;

    Transform & operator=(const Transform & other) = default;

    /**
     * Adds to the transform translation by the components of vector
     * @param vector vector to translate by
     * @return modified transform
     */
    Transform & translate(const Vec3 & vector);

    /**
     * Adds to the transform rotation through angle radians about vector axis
     * @param angle angle to rotate through
     * @param axis axis to rotate about
     * @return modified transform
     */
    Transform & rotate(float angle, const Vec3 & axis);

    /**
     * Adds to transform scale by the components of factor
     * @param factors
     * @return modified transform
     */
    Transform & scale(const Vec3 & factors);

    /**
     * Adds to transform scale by the given factor
     * @param factor factor to scale by
     * @return modified transform
     */
    Transform & scale(float factor);

    /**
     * Returns origin of transformed coordinate system.
     * Same as transform_point(Vec3(0, 0, 0))
     * @return
     */
    Vec3 origin() const;

    /**
     * Returns forward direction.
     * Same as transform_direction(Vec3(1, 0, 0))
     * @return forward direction
     */
    Vec3 forward() const;

    /**
     * Returns left direction.
     * Same as transform_direction(Vec3(0, 1, 0))
     * @return left direction
     */
    Vec3 left() const;

    /**
     * Returns up direction.
     * Same as transform_direction(Vec3(0, 0, 1))
     * @return up direction
     */
    Vec3 up() const;

    /**
     * Applies the transform to point
     * @param point point to apply transform to
     * @return transformed point
     */
    Vec3 transform_point(const Vec3 & point) const;

    /**
     * Applies backward transform to point
     * @param point point to apply backward transform to
     * @return transformed point
     */
    Vec3 untransform_point(const Vec3 & point) const;

    /**
     * Applies the transform to direction
     * @param direction direction to apply transform to
     * @return transformed direction
     */
    Vec3 transform_direction(const Vec3 & direction) const;

    /**
     * Applies backward transform to direction
     * @param direction direction to apply backward transform to
     * @return transformed direction
     */
    Vec3 untransform_direction(const Vec3 & direction) const;

private:
    void recalculate_backward_transform();

    Mat4 forward_transform_matrix_;
    Mat4 backward_transform_matrix_;
};

#endif //RAY_TRACING_TRANSFORM_H
