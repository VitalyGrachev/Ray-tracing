#ifndef RAY_TRACING_RAY_TRACE_TASK_H
#define RAY_TRACING_RAY_TRACE_TASK_H

class RayTracer;

#include "../ray_tracer.h"

/**
 * Interface. Trace task for a ray.
 * Determines ray's contribution into fragment color.
 */
class RayTraceTask {
public:
    virtual ~RayTraceTask() = default;

    /**
     * Perform this task
     * @param ray_tracer ray trace to trace child rays
     */
    virtual void operator()(RayTracer & ray_tracer) = 0;
};

#endif //RAY_TRACING_RAY_TRACE_TASK_H
