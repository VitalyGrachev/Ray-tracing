#include "scene.h"

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
    std::optional<IntersectionTarget> closest_target(std::nullopt);
    float distance_to_closest_target = 0.0f;

    auto closest_intersection_or_nothing = [&](const Geometry & geometry) -> std::optional<Intersection> {
        auto intersection = geometry.find_intersection(ray);
        if (intersection.has_value()) {
            const float distance_to_target = ray.origin().distanceToPoint(intersection->point());
            if (distance_to_target < distance_to_closest_target ||
                !closest_target.has_value()) {
                distance_to_closest_target = distance_to_target;
                return intersection;
            }
        }
        return {};
    };

    for (const LightSource & source : light_sources_) {
        if (auto intersection = closest_intersection_or_nothing(source.geometry())) {
            closest_target.emplace(*intersection, &source);
        }
    }

    for (const Object & object : objects_) {
        if (auto intersection = closest_intersection_or_nothing(object.geometry())) {
            closest_target.emplace(*intersection, &object);
        }
    }

    return closest_target;
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
