#include "light.h"

#include <algorithm>

Light::Light(const Color & color, float intensity)
        : color_(color),
          intensity_(std::clamp(intensity, 0.0f, 1.0f)) {}
