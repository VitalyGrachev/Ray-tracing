#include "mesh.h"

Mesh::Mesh(const std::vector<Triangle> & triangles) : triangles_(triangles) {}

Mesh::Mesh(std::vector<Triangle> && triangles) : triangles_(std::move(triangles)) {}

Enumeration<Mesh::TriangleIterator> Mesh::enumerate_triangles() const {
    return Enumeration<Mesh::TriangleIterator>{triangles_.cbegin(), triangles_.cend()};
}

std::optional<Intersection> Mesh::find_intersection(const Ray & ray) const {
    std::optional<Intersection> closest_intersection;
    float distance_to_closest_intersection = 0.0f;

    for (const auto & triangle : enumerate_triangles()) {
        auto intersection = triangle.find_intersection(ray);
        if (intersection.has_value()) {
            const float distance_to_target = ray.origin().distanceToPoint(intersection->point());
            if (distance_to_target < distance_to_closest_intersection ||
                !closest_intersection.has_value()) {
                distance_to_closest_intersection = distance_to_target;
                closest_intersection = intersection;
            }
        }
    }
    return closest_intersection;
}
