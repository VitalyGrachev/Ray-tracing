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
     * Returns forward-facing vector.
     * Same as map_to_world(Vec3(1, 0, 0)
     * @return forward-facing vector
     */
    Vec3 forward() const;

    /**
     * Returns lift-facing vector.
     * Same as map_to_world(Vec3(0, 1, 0)
     * @return lift-facing vector
     */
    Vec3 left() const;

    /**
     * Returns up-facing vector.
     * Same as map_to_world(Vec3(0, 0, 1)
     * @return up-facing vector
     */
    Vec3 up() const;

    /**
     * Applies the transform to vector vector
     * @param vector vector to apply transform to
     * @return transformed vector
     */
    Vec3 apply(const Vec3 & vector) const;

    /**
     * Applies backward transform to vector
     * @param vector vector to apply backward transform to
     * @return transformed vector
     */
    Vec3 unapply(const Vec3 & vector) const;

private:
    void recalculate_backward_transform();

    Mat4 forward_transform_matrix_;
    Mat4 backward_transform_matrix_;
};

#endif //RAY_TRACING_TRANSFORM_H
