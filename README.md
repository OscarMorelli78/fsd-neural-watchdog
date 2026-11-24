# fsd-neural-watchdog

Experimental C++20 ring-buffer and threshold evaluator. Research prototype only; not validated for vehicle control, Tesla hardware, or safety-critical deployment.

## Current scope
- Fixed-size ring buffer and threshold comparisons on supplied entropy and distance values.
- Entropy computation, Mahalanobis computation and temporal flicker detection are not implemented in the current evaluator.
- No verified target-hardware latency or safety claims. The benchmark source is experimental.

## Roadmap
Establish a reproducible build, unit tests, boundary checks and measured benchmark results before making performance claims.
