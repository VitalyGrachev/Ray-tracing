#ifndef RAY_TRACING_VECTOR_H
#define RAY_TRACING_VECTOR_H

#include <QVector2D>
#include <QVector3D>

using Vec2 = QVector2D;
using Vec3 = QVector3D;

/**
 * Returns dot product of given vectors
 * @param a vector
 * @param b vector
 * @return dot product of given vectors
 */
inline float dot(const Vec3 & a, const Vec3 & b) {
    return Vec3::dotProduct(a, b);
}

/**
 * Returns cross product of given vectors
 * @param a vector
 * @param b vector
 * @return cross product of given vectors
 */
inline Vec3 cross(const Vec3 & a, const Vec3 & b) {
    return Vec3::crossProduct(a, b);
}

inline std::ostream & operator<<(std::ostream & os, const Vec2 & v) {
    os << '(' << v.x() << ' ' << v.y() << ')';
    return os;
}

inline std::ostream & operator<<(std::ostream & os, const Vec3 & v) {
    os << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ')';
    return os;
}

#endif //RAY_TRACING_VECTOR_H
