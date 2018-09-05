#include "object.h"

Object::Object(const std::shared_ptr<Geometry> & geometry,
               const std::shared_ptr<Material> & material)
        : geometry_(geometry),
          material_(material) {}
