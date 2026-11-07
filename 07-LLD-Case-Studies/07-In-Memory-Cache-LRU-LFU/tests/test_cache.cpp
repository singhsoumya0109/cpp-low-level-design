#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <optional>

class SimpleLRU {
    size_t cap_;
    std::list<std::pair<int, int>> l_;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_;
public:
    explicit SimpleLRU(size_t cap) : cap_(cap) {}
    void put(int k, int v) {
        if (m_.count(k)) {
            m_[k]->second = v;
            l_.splice(l_.begin(), l_, m_[k]);
            return;
        }
        if (l_.size() >= cap_) {
            m_.erase(l_.back().first);
            l_.pop_back();
        }
        l_.push_front({k, v});
        m_[k] = l_.begin();
    }
    std::optional<int> get(int k) {
        if (!m_.count(k)) return std::nullopt;
        l_.splice(l_.begin(), l_, m_[k]);
        return m_[k]->second;
    }
};

int main() {
    std::cout << "[TEST] Running LRU Cache tests...\n";
    SimpleLRU cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    assert(cache.get(1) == 10);
    cache.put(3, 30); // Evicts 2
    assert(!cache.get(2).has_value());
    assert(cache.get(3) == 30);
    std::cout << "[TEST] All LRU Cache tests PASSED!\n";
    return 0;
}
