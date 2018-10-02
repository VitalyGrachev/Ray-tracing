#ifndef RAY_TRACING_VECTOR_H
#define RAY_TRACING_VECTOR_H

#include <QVector2D>
#include <QVector3D>

using Vec2 = QVector2D;
using Vec3 = QVector3D;

inline std::ostream & operator<<(std::ostream & os, const Vec2 & v) {
    os << '(' << v.x() << ' ' << v.y() << ')';
    return os;
}

inline std::ostream & operator<<(std::ostream & os, const Vec3 & v) {
    os << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ')';
    return os;
}

#endif //RAY_TRACING_VECTOR_H
