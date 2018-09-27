#include "fragment_render_task.h"

FragmentRenderTask::FragmentRenderTask(FinishedFragmentCounter & fragment_counter, Color & fragment_color)
        : Fragment(fragment_color),
          fragment_counter_(fragment_counter) {}

FragmentRenderTask::~FragmentRenderTask() {
    fragment_counter_.get().fragment_finished();
}

void FragmentRenderTask::add_color(const Color & color) {
    std::lock_guard lock(mutex_);
    Fragment::add_color(color);
}
