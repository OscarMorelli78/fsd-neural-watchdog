# fsd-neural-watchdog

Zero-allocation C++20 edge evaluator for Tesla HW4/AI4 SoC architectures. Captures pre-causal $t_0$ neural drift buffers before macro physical triggers or human disengagements occur.

## Key Features
- **Zero Heap Allocations:** Fully deterministic runtime using compile-time static ring buffers (`alignas(64)`).
- **Sub-Microsecond Latency:** Runs asynchronously on ARM Cortex cores in <300 CPU cycles (<85 ns).
- **Triple-Trigger Evaluation:**
  1. Discrete Mode-Entropy ($H_{out}$) via IEEE-754 bit-manipulation log2 approximation.
  2. Diagonal Mahalanobis Distance ($D_{lat}$) for Out-of-Distribution (OOD) latent space detection.
  3. Temporal Flicker Detection via $N=8$ circular argmax buffer.

## Architecture & Benchmark
