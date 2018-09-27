#include "base_ray_trace_task.h"

BaseRayTraceTask::BaseRayTraceTask(const std::shared_ptr<Fragment> & fragment,
                                   const Scene & scene,
                                   const Ray & ray,
                                   const Color & color_intensity)
        : ray_(ray),
          fragment_(fragment),
          scene_(scene),
          color_intensity_(color_intensity) {}

BaseRayTraceTask::BaseRayTraceTask(const BaseRayTraceTask & parent, const Ray & ray, const Color & color_intensity)
        : ray_(ray),
          fragment_(parent.fragment_),
          scene_(parent.scene_),
          color_intensity_(parent.color_intensity_ * color_intensity) {}

void BaseRayTraceTask::submit_color(const Color & color) {
    fragment_->add_color(color_intensity_ * color);
}
