#include "finished_fragment_counter.h"

void FinishedFragmentCounter::fragment_finished() {
    const unsigned fragments_left = --pending_fragments_;
    if (!fragments_left) {
        on_all_finished_();
    }
}