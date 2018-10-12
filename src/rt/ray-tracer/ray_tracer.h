#ifndef RAY_TRACING_RAY_TRACER_H
#define RAY_TRACING_RAY_TRACER_H

#include <memory>

class RayTraceTask;

#include "ray-trace-task/ray_trace_task.h"

/**
 * Interface. Performs given ray trace tasks.
 */
class RayTracer {
public:
    virtual ~RayTracer() = default;

    /**
     * Performs given ray trace task
     * @param ray trace task to perform
     */
    virtual void trace_ray(std::unique_ptr<RayTraceTask> && ray) = 0;
};

#endif //RAY_TRACING_RAY_TRACER_H
