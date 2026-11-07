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
        if (size_ < capacity_) ++size_;
        else head_ = (head_ + 1) % capacity_;
    }
    // TODO: Implement custom iterator for FIFO traversal
};

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
