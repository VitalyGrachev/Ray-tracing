#ifndef RAY_TRACING_FINISHED_FRAGMENT_COUNTER_H
#define RAY_TRACING_FINISHED_FRAGMENT_COUNTER_H

#include <atomic>
#include <functional>

/**
 * Counter of finished fragments to spot finish of rendering
 */
class FinishedFragmentCounter {
public:
    /**
     * Creates finished fragment counter, invokes given callable when given number of fragments finish rendering
     * @param pending_fragments fragments count to finish rendering
     * @param on_all_finished callback to invoke when rendering finished
     */
    template<class F>
    FinishedFragmentCounter(unsigned pending_fragments, F && on_all_finished);

    virtual ~FinishedFragmentCounter() = default;

    /**
     * @return true if render is finished, false otherwise
     */
    bool is_render_finished() const;

    /**
     * Receives the report, that fragment is finished
     */
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
