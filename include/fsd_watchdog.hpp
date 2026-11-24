#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <cmath>

namespace tesla::edge {

// Research-only compatibility API; not validated for vehicle control.
struct alignas(64) NeuralStateFrame {
    std::uint64_t timestamp_us;
    float entropy_score;
    float mahalanobis_dist;
    std::uint8_t selected_mode;
};

template <std::size_t BufferSize = 150>
class PreCausalWatchdog {
    static_assert(BufferSize > 0, "BufferSize must be positive");
    std::array<NeuralStateFrame, BufferSize> ring_buffer_{};
    std::size_t head_{0};
    std::size_t count_{0};
    float h_threshold_;
    float d_threshold_;
public:
    // Third argument retained for source compatibility; flicker not implemented.
    constexpr PreCausalWatchdog(float h_th, float d_th, std::uint8_t) noexcept
        : h_threshold_(h_th), d_threshold_(d_th) {}

    [[nodiscard]] bool evaluate_and_push(std::uint64_t ts, float h_out, float d_lat, std::uint8_t mode) noexcept {
        if (!std::isfinite(h_out) || !std::isfinite(d_lat)) return true;
        ring_buffer_[head_] = {ts, h_out, d_lat, mode};
        head_ = (head_ + 1) % BufferSize;
        if (count_ < BufferSize) ++count_;
        return h_out >= h_threshold_ || d_lat >= d_threshold_;
    }

    [[nodiscard]] constexpr std::size_t get_pre_causal_index(std::size_t offset = 75) const noexcept {
        return (head_ + BufferSize - (offset % BufferSize)) % BufferSize;
    }
    [[nodiscard]] constexpr std::size_t size() const noexcept { return count_; }
};
} // namespace tesla::edge
