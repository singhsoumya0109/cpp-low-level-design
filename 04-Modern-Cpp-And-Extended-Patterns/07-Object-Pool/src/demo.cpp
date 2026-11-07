#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <string>

template <typename T>
class ObjectPool : public std::enable_shared_from_this<ObjectPool<T>> {
public:
    using Deleter = std::function<void(T*)>;
    using PooledPtr = std::unique_ptr<T, Deleter>;

    explicit ObjectPool(size_t initial_capacity = 10) {
        for (size_t i = 0; i < initial_capacity; ++i) {
            pool_.push_back(std::make_unique<T>());
        }
    }

    PooledPtr acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::unique_ptr<T> item;
        if (pool_.empty()) {
            item = std::make_unique<T>();
        } else {
            item = std::move(pool_.back());
            pool_.pop_back();
        }

        std::weak_ptr<ObjectPool<T>> weak_pool = this->shared_from_this();
        return PooledPtr(item.release(), [weak_pool](T* raw_ptr) {
            if (auto shared_pool = weak_pool.lock()) {
                std::lock_guard<std::mutex> lk(shared_pool->mutex_);
                shared_pool->pool_.push_back(std::unique_ptr<T>(raw_ptr));
            } else {
                delete raw_ptr; // pool is destroyed, clean up object
            }
        });
    }

    size_t available() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return pool_.size();
    }

private:
    mutable std::mutex mutex_;
    std::vector<std::unique_ptr<T>> pool_;
};

struct Connection {
    int id;
    static inline int counter = 0;
    Connection() : id(++counter) {
        std::cout << "[Connection " << id << "] Created\n";
    }
    void query(const std::string& q) {
        std::cout << "[Connection " << id << "] Executing: " << q << "\n";
    }
};

int main() {
    std::cout << "=== Modern C++ Object Pool Demo ===\n";
    auto pool = std::make_shared<ObjectPool<Connection>>(3);
    std::cout << "Initial available: " << pool->available() << "\n";

    {
        auto conn1 = pool->acquire();
        conn1->query("SELECT 1;");
        std::cout << "Available after 1 acquire: " << pool->available() << "\n";

        {
            auto conn2 = pool->acquire();
            conn2->query("SELECT 2;");
            std::cout << "Available after 2 acquires: " << pool->available() << "\n";
        } // conn2 returned to pool automatically here!

        std::cout << "Available after conn2 release: " << pool->available() << "\n";
    } // conn1 returned to pool automatically here!

    std::cout << "Available after conn1 release: " << pool->available() << "\n";
    return 0;
}
