#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <optional>
#include <mutex>

// Thread-safe LRU Cache Implementation
template <typename K, typename V>
class LRUCache {
    size_t capacity_;
    mutable std::mutex mtx_;
    std::list<std::pair<K, V>> items_list_;
    using ListIterator = typename std::list<std::pair<K, V>>::iterator;
    std::unordered_map<K, ListIterator> lookup_;

public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}

    std::optional<V> get(const K& key) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = lookup_.find(key);
        if (it == lookup_.end()) return std::nullopt;

        // Move accessed item to front of LRU list
        items_list_.splice(items_list_.begin(), items_list_, it->second);
        return it->second->second;
    }

    void put(const K& key, const V& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = lookup_.find(key);
        if (it != lookup_.end()) {
            // Update existing value and promote to front
            it->second->second = value;
            items_list_.splice(items_list_.begin(), items_list_, it->second);
            return;
        }

        // Evict LRU element if at capacity
        if (items_list_.size() >= capacity_) {
            auto lru = items_list_.back();
            lookup_.erase(lru.first);
            items_list_.pop_back();
        }

        // Insert new entry at front
        items_list_.emplace_front(key, value);
        lookup_[key] = items_list_.begin();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return items_list_.size();
    }
};

int main() {
    std::cout << "=== LRU Cache Simulation ===\n";
    LRUCache<std::string, int> cache(2);

    cache.put("A", 100);
    cache.put("B", 200);
    std::cout << "Get A: " << cache.get("A").value_or(-1) << "\n"; // Promotes A

    cache.put("C", 300); // Evicts B (since A was recently accessed)

    std::cout << "Get B (evicted): " << (cache.get("B") ? "Found" : "Null") << "\n";
    std::cout << "Get C: " << cache.get("C").value_or(-1) << "\n";
    return 0;
}
