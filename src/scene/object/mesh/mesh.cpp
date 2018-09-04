#include "mesh.h"

Enumeration<Mesh::TriangleIterator> Mesh::enumerate_triangles() const {
    return Enumeration<Mesh::TriangleIterator>{triangles_.cbegin(), triangles_.cend()};
}
