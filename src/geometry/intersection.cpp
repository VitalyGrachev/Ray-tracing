#include "intersection.h"

Intersection::Intersection(const Vec3 & point,
                           const Vec3 & normal,
                           const Vec2 & uv)
        : point_(point),
          normal_(normal),
          tex_coords_(uv) {}
