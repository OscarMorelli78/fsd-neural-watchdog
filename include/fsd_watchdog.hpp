#pragma once
#include 
#include 
#include 
#include 

namespace tesla::edge {

struct alignas(64) NeuralStateFrame {
    uint64_t timestamp_us;
    float entropy_score;
    float mahalanobis_dist;
    uint8_t selected_mode;
};

template  // ~5s a 30 FPS
class PreCausalWatchdog {
private:
    alignas(64) std::array ring_buffer_{};
    std::size_t head_{0};
    
    float h_threshold_;
    float d_threshold_;
    uint8_t flicker_threshold_;

public:
    constexpr PreCausalWatchdog(float h_th, float d_th, uint8_t f_th) noexcept 
        : h_threshold_(h_th), d_threshold_(d_th), flicker_threshold_(f_th) {}

    [[nodiscard]] inline bool evaluate_and_push(uint64_t ts, float h_out, float d_lat, uint8_t mode) noexcept {
        ring_buffer_[head_] = {ts, h_out, d_lat, mode};
        head_ = (head_ + 1) % BufferSize;

        // Evaluación rápida O(1) sin asignación dinámica
        return (h_out >= h_threshold_) || (d_lat >= d_threshold_);
    }

    [[nodiscard]] constexpr std::size_t get_pre_causal_index(std::size_t offset = 75) const noexcept {
        return (head_ >= offset) ? (head_ - offset) : (BufferSize - (offset - head_));
    }
};

} // namespace tesla::edge
