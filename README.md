# fsd-neural-watchdog

Experimental C++20 ring-buffer and threshold evaluator. Research prototype only; not validated for vehicle control, Tesla hardware, or safety-critical deployment.

## Current scope
- Fixed-size ring buffer and threshold comparisons on supplied entropy and distance values.
- Entropy computation, Mahalanobis computation and temporal flicker detection are not implemented in the current evaluator.
- No verified target-hardware latency or safety claims. The benchmark source is experimental.

## Build and run the tests

From the repository root with a C++20 compiler:

```sh
g++ -std=c++20 -Wall -Wextra -Werror -pedantic tests/test_watchdog.cpp -o watchdog_test
./watchdog_test
```

The tests exercise ring-buffer and threshold boundaries. GitHub Actions runs the same commands for pull requests and pushes to Main. Benchmark measurements remain experimental.
