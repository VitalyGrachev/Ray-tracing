#include "light_source.h"

LightSource::LightSource(const Light & light,
                         LightSource::Type source_type,
                         const std::shared_ptr<Geometry> & geometry,
                         const Transform & transform)
        : transform_(transform),
          light_(light),
          geometry_(geometry),
          source_type_(source_type) {}
