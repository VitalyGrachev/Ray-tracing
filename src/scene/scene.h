#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

#include <vector>
#include <optional>
#include "camera/camera.h"
#include "object/object.h"
#include "light/light_source.h"
#include "intersection_target.h"
#include "../util/enumeration.h"

/**
 * Represents graphical scene containing group of visible objects lit by group of light sources and associated camera
 */
class Scene final {
    std::vector<Object> objects_;
    std::vector<std::unique_ptr<LightSource>> light_sources_;
    Camera camera_;
public:
    using ObjectsIterator = decltype(objects_)::iterator;
    using ConstObjectsIterator = decltype(objects_)::const_iterator;
    using LightSourcesIterator = decltype(light_sources_)::iterator;
    using ConstLightSourcesIterator = decltype(light_sources_)::const_iterator;

    /**
     * Creates empty scene and associates the given camera with it
     * @param camera camera to associate with the scene
     */
    explicit Scene(const Camera & camera = Camera());

    Scene(const Scene & other) = delete;

    Scene(Scene && other);

    ~Scene() = default;

    Scene & operator=(const Scene & other) = delete;

    Scene & operator=(Scene && other);

    /**
     * Swaps contents of this scene and other
     * @param other scene to swap contents with
     */
    void swap(Scene & other);

    /**
     * Returns camera associated with the scene
     * @return camera associated with the scene
     */
    Camera & get_camera() { return camera_; }

    const Camera & get_camera() const { return camera_; }

    /**
     * Finds closest to ray origin intersection of ray and scene's object or light source
     * @param ray ray to find intersection with
     * @param max_distance maximum distance from origin to serch for intersections
     * @return std::optional containing found intersection or empty std::optional if there is no intersection
     */
    std::optional<IntersectionTarget>
    find_intersection(const Ray & ray, float max_distance = std::numeric_limits<float>::infinity()) const;

    /**
     * Returns enumeration of objects contained by the scene
     * @return enumeration of objects
     */
    Enumeration<ObjectsIterator> enumerate_objects();

    Enumeration<ConstObjectsIterator> enumerate_objects() const;

    /**
     * Returns enumeration of light sources, contained by the scene
     * @return enumeration of light sources
     */
    Enumeration<LightSourcesIterator> enumerate_light_sources();

    Enumeration<ConstLightSourcesIterator> enumerate_light_sources() const;

    /**
     * Adds new object to the scene
     * @param object object to add
     */
    void add_object(const Object & object);

    /**
     * Adds new light source to the scene
     * @param light source light source to add
     */
    void add_light_source(std::unique_ptr<LightSource> && light_source);
};

/**
 * Swaps contents of given scenes
 */
void swap(Scene & a, Scene & b);

#endif //RAY_TRACING_SCENE_H
