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
