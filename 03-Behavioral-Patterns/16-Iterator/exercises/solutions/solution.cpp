#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class CircularBuffer {
    std::vector<T> buffer_;
    size_t head_ = 0;
    size_t size_ = 0;
    size_t capacity_;
public:
    explicit CircularBuffer(size_t cap) : buffer_(cap), capacity_(cap) {}

    void push(T val) {
        size_t idx = (head_ + size_) % capacity_;
        buffer_[idx] = val;
        if (size_ < capacity_) {
            ++size_;
        } else {
            head_ = (head_ + 1) % capacity_;
        }
    }

    size_t size() const { return size_; }

    T operator[](size_t i) const {
        return buffer_[(head_ + i) % capacity_];
    }
};

int main() {
    CircularBuffer<int> cb(3);
    cb.push(10);
    cb.push(20);
    cb.push(30);
    cb.push(40); // Overwrites 10; items are now 20, 30, 40

    assert(cb.size() == 3);
    assert(cb[0] == 20);
    assert(cb[1] == 30);
    assert(cb[2] == 40);

    std::cout << "Iterator solution verified successfully!\n";
    return 0;
}
