#include "eye_ray_trace_task_factory.h"

#include "../ray-trace-task/air_ray_trace_task.h"

EyeRayTraceTaskFactory::EyeRayTraceTaskFactory(const Scene & scene,
                                               const Color & color_intensity,
                                               unsigned int max_recursion_depth)
        : scene_(scene),
          color_intensity_(color_intensity),
          max_recursion_depth_(max_recursion_depth) {}

std::unique_ptr<RayTraceTask> EyeRayTraceTaskFactory::create(const Ray & ray,
                                                             const std::shared_ptr<Fragment> & fragment) {
    return std::make_unique<AirRayTraceTask>(fragment,
                                             ray,
                                             scene_,
                                             color_intensity_,
                                             max_recursion_depth_);
}
