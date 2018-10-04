#include "scene.h"

#include "../geometry/ray_transform.h"

namespace {

class ClosestTargetSeeker final {
public:
    explicit ClosestTargetSeeker(const Ray & ray, float max_distance)
            : ray_(ray),
              distance_to_closest_target_(max_distance) {}

    ClosestTargetSeeker & operator=(const ClosestTargetSeeker & other) = delete;

    ~ClosestTargetSeeker() = default;

    ClosestTargetSeeker(const ClosestTargetSeeker & other) = delete;

    void consume_target(const Object & target);

    std::optional<IntersectionTarget> closest_target() const { return closest_target_; }

private:
    std::optional<Intersection> find_intersection_with(const Transform & transform, const Geometry & geometry) const;

    std::optional<IntersectionTarget> closest_target_;
    Ray ray_;
    float distance_to_closest_target_;
};

void ClosestTargetSeeker::consume_target(const Object & target) {
    auto intersection = find_intersection_with(target.transform(), target.geometry());
    if (!intersection) { return; }

    const float distance_to_target = ray_.origin().distanceToPoint(intersection->point());

    if (distance_to_target >= distance_to_closest_target_) { return; }

    distance_to_closest_target_ = distance_to_target;
    closest_target_.emplace(*intersection, target);
}

std::optional<Intersection> ClosestTargetSeeker::find_intersection_with(const Transform & transform,
                                                                        const Geometry & geometry) const {
    // Transform ray into model coordinates since geometry defined in it.
    Ray model_ray = untransform_ray(transform, ray_);
    auto intersection = geometry.find_intersection(model_ray);

    if (!intersection) { return std::nullopt; }

    // Transform resulting intersection into world coordinates
    return std::make_optional<Intersection>(transform.transform_point(intersection->point()),
                                            transform.transform_direction(intersection->normal()),
                                            intersection->tex_coords());
}

}

Scene::Scene(const Camera & camera)
        : camera_(camera) {}

Scene::Scene(Scene && other)
        : objects_(std::move(other.objects_)),
          light_sources_(std::move(other.light_sources_)),
          camera_(other.camera_) {}

Scene & Scene::operator=(Scene && other) {
    swap(other);
    return *this;
}

std::optional<IntersectionTarget> Scene::find_intersection(const Ray & ray, float max_distance) const {
    ClosestTargetSeeker target_seeker(ray, max_distance);

    for (const Object & object : objects_) {
        target_seeker.consume_target(object);
    }

    return target_seeker.closest_target();
}

Enumeration<Scene::ObjectsIterator> Scene::enumerate_objects() {
    return Enumeration<Scene::ObjectsIterator>(objects_.begin(), objects_.end());
}

Enumeration<Scene::ConstObjectsIterator> Scene::enumerate_objects() const {
    return Enumeration<Scene::ConstObjectsIterator>(objects_.cbegin(), objects_.cend());
}

Enumeration<Scene::LightSourcesIterator> Scene::enumerate_light_sources() {
    return Enumeration<Scene::LightSourcesIterator>(light_sources_.begin(), light_sources_.end());
}

Enumeration<Scene::ConstLightSourcesIterator> Scene::enumerate_light_sources() const {
    return Enumeration<Scene::ConstLightSourcesIterator>(light_sources_.cbegin(), light_sources_.cend());
}

void Scene::add_object(const Object & object) {
    objects_.push_back(object);
}

void Scene::add_light_source(std::unique_ptr<LightSource> && light_source) {
    light_sources_.push_back(std::move(light_source));
}

void Scene::swap(Scene & other) {
    if (this == &other) { return; }

    using std::swap;
    swap(objects_, other.objects_);
    swap(light_sources_, other.light_sources_);

    Camera tmp = camera_;
    camera_ = other.camera_;
    other.camera_ = tmp;
}

void swap(Scene & a, Scene & b) {
    a.swap(b);
}
