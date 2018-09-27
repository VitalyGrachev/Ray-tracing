#ifndef RAY_TRACING_RAY_TRACE_TASK_H
#define RAY_TRACING_RAY_TRACE_TASK_H

class RayTracer;

#include "../ray_tracer.h"

/**
 * Interface.
 */
class RayTraceTask {
public:
    virtual ~RayTraceTask() = default;

    virtual void operator()(RayTracer & ray_tracer) = 0;
};

#endif //RAY_TRACING_RAY_TRACE_TASK_H
