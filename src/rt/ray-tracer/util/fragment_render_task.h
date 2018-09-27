#ifndef RAY_TRACING_FRAGMENT_RENDER_TASK_H
#define RAY_TRACING_FRAGMENT_RENDER_TASK_H

#include <memory>
#include <mutex>

#include "../../frame/fragment.h"
#include "finished_fragment_counter.h"

class FragmentRenderTask : public Fragment {
public:
    FragmentRenderTask(FinishedFragmentCounter & fragment_counter, Color & fragment_color);

    ~FragmentRenderTask();

    void add_color(const Color & color) override;

private:
    std::reference_wrapper<FinishedFragmentCounter> fragment_counter_;
    std::mutex mutex_;
};

#endif //RAY_TRACING_FRAGMENT_RENDER_TASK_H
