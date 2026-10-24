/**
 * @file solution.cpp
 * @brief Reference solutions for Singleton Exercises.
 */

#include <iostream>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

// Exercise 1 Solution: SessionRegistry
class SessionRegistry {
private:
    std::unordered_set<std::string> sessions_;
    mutable std::mutex mtx_;

    SessionRegistry() = default;

public:
    SessionRegistry(const SessionRegistry&) = delete;
    SessionRegistry& operator=(const SessionRegistry&) = delete;

    static SessionRegistry& getInstance() {
        static SessionRegistry instance;
        return instance;
    }

    void addSession(std::string_view id) {
        std::lock_guard<std::mutex> lock(mtx_);
        sessions_.insert(std::string(id));
    }

    void removeSession(std::string_view id) {
        std::lock_guard<std::mutex> lock(mtx_);
        sessions_.erase(std::string(id));
    }

    bool isValid(std::string_view id) const {
        std::lock_guard<std::mutex> lock(mtx_);
        return sessions_.find(std::string(id)) != sessions_.end();
    }
};

// Exercise 3 Solution: Thread-Safe Reader-Writer Cache
class InMemoryCache {
private:
    std::unordered_map<std::string, std::string> cache_;
    mutable std::shared_mutex rwMtx_;

    InMemoryCache() = default;

public:
    InMemoryCache(const InMemoryCache&) = delete;
    InMemoryCache& operator=(const InMemoryCache&) = delete;

    static InMemoryCache& getInstance() {
        static InMemoryCache instance;
        return instance;
    }

    void put(const std::string& key, const std::string& value) {
        std::unique_lock<std::shared_mutex> writeLock(rwMtx_);
        cache_[key] = value;
    }

    std::optional<std::string> get(const std::string& key) const {
        std::shared_lock<std::shared_mutex> readLock(rwMtx_);
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

int main() {
    std::cout << "=== Testing Reference Solutions ===\n";

    // Test Exercise 1
    SessionRegistry::getInstance().addSession("session-abc-123");
    std::cout << "Session valid? "
              << (SessionRegistry::getInstance().isValid("session-abc-123") ? "YES" : "NO") << '\n';

    // Test Exercise 3
    InMemoryCache::getInstance().put("theme", "dark_mode");
    std::cout << "Cache 'theme': "
              << InMemoryCache::getInstance().get("theme").value_or("none") << '\n';

    return 0;
}

