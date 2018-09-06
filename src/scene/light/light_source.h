#ifndef RAY_TRACING_LIGHT_SOURCE_H
#define RAY_TRACING_LIGHT_SOURCE_H

#include <memory>
#include "light.h"
#include "../../geometry/geometry.h"
#include "../../util/transform.h"

/**
 * Piece of geometry that emit light
 */
class LightSource final {
public:
    /**
     * Type of light source
     */
    enum class Type {
        /**
         * Emits light in only forward direction of this light source.
         * Brightness is constant for any distance from light source.
         */
                Directional,

        /**
         * Emits light in every direction.
         * Brightness decreases when distance from light source increases.
         */
                Point
    };

    /**
     * Creates light source with given properties.
     * @param light light emitted by the light source
     * @param source_type type of light source
     * @param geometry visible geometry of the light source
     * @param transform transform of the light source
     */
    LightSource(const Light & light,
                Type source_type,
                const std::shared_ptr<Geometry> & geometry,
                const Transform & transform = Transform());

    LightSource(const LightSource & other) = default;

    LightSource & operator=(const LightSource & other) = default;

    /**
     * Returns transform, which represent placement of light source in world coordinate system
     * @return transform of the light source
     */
    Transform & transform() { return transform_; }

    const Transform & transform() const { return transform_; }

    /**
     * @return Light emitted by light source
     */
    const Light & light() const { return light_; }

    /**
     * @return visible geometry of light source
     */
    const Geometry & geometry() const { return *geometry_; }

    /**
     * @return type of light source
     */
    Type source_type() const { return source_type_; }

private:
    Transform transform_;
    Light light_;
    std::shared_ptr<Geometry> geometry_;
    Type source_type_;
};

#endif //RAY_TRACING_LIGHT_SOURCE_H
