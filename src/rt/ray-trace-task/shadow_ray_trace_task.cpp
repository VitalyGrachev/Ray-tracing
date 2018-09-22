#include "shadow_ray_trace_task.h"

namespace {
constexpr float pi = 3.14159265359f;
}

ShadowRayTraceTask::ShadowRayTraceTask(const BaseRayTraceTask & parent,
                                       const Illuminance & illuminance,
                                       const BRDF & surface_brdf)
        : BaseRayTraceTask(parent, illuminance.ray_to_light_source(), Color(1, 1, 1)),
          surface_brdf_(surface_brdf),
          illuminance_(illuminance.illuminane()),
          distance_to_source_(illuminance.distance_to_source()) {}

void ShadowRayTraceTask::operator()() {
    auto maybe_intersection = scene().find_intersection(ray(), distance_to_source_);
    if (!maybe_intersection) { return; }

    const Color color = pi * surface_brdf_(ray().direction()) * illuminance_;
    submit_color(color);
}
