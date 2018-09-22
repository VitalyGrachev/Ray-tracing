#ifndef RAY_TRACING_RAY_TRACE_TASK_H
#define RAY_TRACING_RAY_TRACE_TASK_H

/**
 * Interface.
 */
class RayTraceTask {
public:
    virtual ~RayTraceTask() = default;

    virtual void operator()() = 0;
};

#endif //RAY_TRACING_RAY_TRACE_TASK_H
