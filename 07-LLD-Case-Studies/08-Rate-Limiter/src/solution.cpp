#include <iostream>
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <memory>
#include <string>

// Token Bucket Rate Limiter
class TokenBucket {
    double capacity_;
    double refill_rate_per_sec_;
    double tokens_;
    std::chrono::steady_clock::time_point last_refill_;
    mutable std::mutex mtx_;

    void refill() {
        auto now = std::chrono::steady_clock::now();
        double elapsed_sec = std::chrono::duration<double>(now - last_refill_).count();
        tokens_ = std::min(capacity_, tokens_ + elapsed_sec * refill_rate_per_sec_);
        last_refill_ = now;
    }

public:
    TokenBucket(double capacity, double refill_rate)
        : capacity_(capacity), refill_rate_per_sec_(refill_rate), tokens_(capacity),
          last_refill_(std::chrono::steady_clock::now()) {}

    bool allow(double tokens = 1.0) {
        std::lock_guard<std::mutex> lock(mtx_);
        refill();
        if (tokens_ >= tokens) {
            tokens_ -= tokens;
            return true;
        }
        return false;
    }
};

class MultiClientRateLimiter {
    double capacity_;
    double refill_rate_;
    std::mutex mtx_;
    std::unordered_map<std::string, std::unique_ptr<TokenBucket>> buckets_;

public:
    MultiClientRateLimiter(double cap, double refill) : capacity_(cap), refill_rate_(refill) {}

    bool allow_request(const std::string& client_id) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = buckets_.find(client_id);
        if (it == buckets_.end()) {
            it = buckets_.emplace(client_id, std::make_unique<TokenBucket>(capacity_, refill_rate_)).first;
        }
        return it->second->allow();
    }
};

int main() {
    std::cout << "=== Rate Limiter Simulation ===\n";
    MultiClientRateLimiter limiter(3, 1.0); // 3 tokens max, 1 token/sec refill

    std::string user = "client_192_168_1_5";
    for (int i = 1; i <= 5; ++i) {
        bool allowed = limiter.allow_request(user);
        std::cout << "Request #" << i << ": " << (allowed ? "ALLOWED (200)" : "REJECTED (429)") << "\n";
    }
    return 0;
}
