#include <benchmark/benchmark.h>
#include "../include/fsd_watchdog.hpp"

static void BM_TwoThresholdEvaluation(benchmark::State& state) {
    tesla::edge::PreCausalWatchdog<150> watchdog(0.85f, 15.0f, 3);
    uint64_t ts = 1000000;
    
    for (auto _ : state) {
        bool triggered = watchdog.evaluate_and_push(ts++, 0.92f, 18.4f, 2);
        benchmark::DoNotOptimize(triggered);
    }
}
BENCHMARK(BM_TwoThresholdEvaluation);

BENCHMARK_MAIN();
