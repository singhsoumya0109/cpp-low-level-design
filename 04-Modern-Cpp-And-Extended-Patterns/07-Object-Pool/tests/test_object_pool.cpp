#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <functional>

template <typename T>
class ObjectPool : public std::enable_shared_from_this<ObjectPool<T>> {
public:
    using Deleter = std::function<void(T*)>;
    using PooledPtr = std::unique_ptr<T, Deleter>;

    explicit ObjectPool(size_t cap = 2) {
        for (size_t i = 0; i < cap; ++i) pool_.push_back(std::make_unique<T>());
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
        std::weak_ptr<ObjectPool<T>> weak_self = this->shared_from_this();
        return PooledPtr(item.release(), [weak_self](T* ptr) {
            if (auto self = weak_self.lock()) {
                std::lock_guard<std::mutex> lk(self->mutex_);
                self->pool_.push_back(std::unique_ptr<T>(ptr));
            } else {
                delete ptr;
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

struct Dummy { int val = 0; };

int main() {
    std::cout << "[TEST] Running Object Pool tests...\n";

    auto pool = std::make_shared<ObjectPool<Dummy>>(2);
    assert(pool->available() == 2);

    {
        auto obj1 = pool->acquire();
        assert(pool->available() == 1);
        obj1->val = 42;

        {
            auto obj2 = pool->acquire();
            assert(pool->available() == 0);
        }
        // obj2 returned
        assert(pool->available() == 1);
    }
    // obj1 returned
    assert(pool->available() == 2);

    std::cout << "[TEST] All Object Pool tests PASSED!\n";
    return 0;
}
