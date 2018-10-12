#ifndef RAY_TRACING_FRAGMENT_RENDER_TASK_H
#define RAY_TRACING_FRAGMENT_RENDER_TASK_H

#include <memory>
#include <mutex>

#include "../../frame/fragment.h"
#include "finished_fragment_counter.h"

/**
 * Fragment which reports to fragment counter on it's deletion
 */
class FragmentRenderTask : public Fragment {
public:
    /**
     * Creates fragment render task which reports to given finished fragment counter
     * @param fragment_counter fragment counter to report to
     * @param fragment_color reference to fragment of frame buffer which accumulates color
     */
    FragmentRenderTask(FinishedFragmentCounter & fragment_counter, Color & fragment_color);

    ~FragmentRenderTask();

    /**
     * Adds given color to fragment color
     * @param color color to add
     */
    void add_color(const Color & color) override;

private:
    std::reference_wrapper<FinishedFragmentCounter> fragment_counter_;
    std::mutex mutex_;
};

#endif //RAY_TRACING_FRAGMENT_RENDER_TASK_H
