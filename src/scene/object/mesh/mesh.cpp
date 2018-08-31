#include "mesh.h"

std::optional<Intersection> Mesh::find_intersection(const Ray & ray) const {
    std::optional<Intersection> closest_intersection;
    float min_distance = 0.0f;
    for (const Triangle & tr : triangles_) {
        const std::optional<Intersection> intersection = Intersection::find(tr, ray);

        if (intersection.has_value()) {
            const float distance = (intersection->point() - ray.start_point()).length();
            if (!closest_intersection.has_value() ||
                distance < min_distance) {
                closest_intersection = intersection;
                min_distance = distance;
            }
        }
    }
    return closest_intersection;
}
