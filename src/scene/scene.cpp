#include "scene.h"

namespace {

class ClosestTargetSeeker final {
public:
    explicit ClosestTargetSeeker(const Ray & ray) : ray_(ray) {}

    ClosestTargetSeeker & operator=(const ClosestTargetSeeker & other) = delete;

    ~ClosestTargetSeeker() = default;

    ClosestTargetSeeker(const ClosestTargetSeeker & other) = delete;

    template<class Target>
    void consume_target(const Target & target);

    std::optional<IntersectionTarget> closest_target() const { return closest_target_; }

private:
    std::optional<Intersection> find_intersection_with(const Transform & transform, const Geometry & geometry) const;

    std::optional<IntersectionTarget> closest_target_;
    Ray ray_;
    float distance_to_closest_target_;
};

template<class Target>
void ClosestTargetSeeker::consume_target(const Target & target) {
    auto maybe_intersection = find_intersection_with(target.transform(), target.geometry());
    if (maybe_intersection.has_value()) {
        const float distance_to_target = ray_.origin().distanceToPoint(maybe_intersection->point());
        if (distance_to_target < distance_to_closest_target_ ||
            !closest_target_.has_value()) {
            distance_to_closest_target_ = distance_to_target;
            closest_target_.emplace(*maybe_intersection, &target);
        }
    }
}

std::optional<Intersection> ClosestTargetSeeker::find_intersection_with(const Transform & transform,
                                                                        const Geometry & geometry) const {
    // Transform ray into model coordinates since geometry defined in it.
    Ray model_ray(transform.untransform_point(ray_.origin()),
                  transform.untransform_direction(ray_.direction()));
    auto maybe_intersection = geometry.find_intersection(model_ray);

    if (!maybe_intersection.has_value()) { return std::nullopt; }

    // Transform resulting intersection into world coordinates
    return std::make_optional<Intersection>(transform.transform_point(maybe_intersection->point()),
                                            transform.transform_direction(maybe_intersection->normal()),
                                            maybe_intersection->tex_coords());
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

std::optional<IntersectionTarget> Scene::find_intersection(const Ray & ray) const {
    ClosestTargetSeeker target_seeker(ray);

    for (const LightSource & source : light_sources_) {
        target_seeker.consume_target(source);
    }

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

void Scene::add_light_source(const LightSource & light_source) {
    light_sources_.push_back(light_source);
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
