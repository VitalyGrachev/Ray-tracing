#ifndef RAY_TRACING_FINISHED_FRAGMENT_COUNTER_H
#define RAY_TRACING_FINISHED_FRAGMENT_COUNTER_H

#include <atomic>
#include <functional>

class FinishedFragmentCounter {
public:
    template<class F>
    FinishedFragmentCounter(unsigned pending_fragments, F && on_all_finished);

    virtual ~FinishedFragmentCounter() = default;

    bool is_render_finished() const;

    void fragment_finished();

private:
    std::atomic_uint pending_fragments_;
    std::function<void()> on_all_finished_;
};

template<class F>
FinishedFragmentCounter::FinishedFragmentCounter(unsigned pending_fragments, F && on_all_finished)
        : pending_fragments_(pending_fragments),
          on_all_finished_(std::move(on_all_finished)) {}

inline bool FinishedFragmentCounter::is_render_finished() const {
    return !pending_fragments_;
}

#endif //RAY_TRACING_FINISHED_FRAGMENT_COUNTER_H
