#include "object.h"

Object::Object(const std::shared_ptr<Mesh> & mesh,
               const std::shared_ptr<Material> & material)
        : mesh_(mesh),
          material_(material) {}
