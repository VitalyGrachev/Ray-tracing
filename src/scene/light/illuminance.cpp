#include "illuminance.h"

Illuminance::Illuminance(const Ray & direction_to_light_source,
                         const Color & illuminance,
                         float distance_to_source)
        : direction_to_source_(direction_to_light_source),
          illuminance_(illuminance),
          distance_to_source_(distance_to_source) {}
