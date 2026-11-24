#include "../include/fsd_watchdog.hpp"
#include <cassert>
#include <limits>
int main() {
    tesla::edge::PreCausalWatchdog<4> w(0.85f, 15.0f, 3);
    assert(w.size() == 0);
    assert(!w.evaluate_and_push(1, 0.2f, 1.0f, 0));
    assert(w.evaluate_and_push(2, 0.85f, 1.0f, 0));
    assert(w.evaluate_and_push(3, 0.2f, 15.0f, 0));
    assert(!w.evaluate_and_push(4, 0.2f, 1.0f, 0));
    assert(w.size() == 4);
    assert(w.get_pre_causal_index(1) == 3);
    assert(w.get_pre_causal_index(5) == 3);
    assert(w.evaluate_and_push(5, std::numeric_limits<float>::quiet_NaN(), 1.0f, 0));
    assert(w.get_pre_causal_index(1) == 3);
    assert(!w.evaluate_and_push(6, 0.2f, 1.0f, 0));
    assert(w.get_pre_causal_index(1) == 0);
}
