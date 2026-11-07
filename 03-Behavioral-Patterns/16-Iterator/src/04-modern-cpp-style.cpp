#include <iostream>
#include <vector>
#include <iterator>

// Modern C++17 STL-compatible forward iterator
// Enables native range-based for loops: for (auto item : container)
template <typename T>
class SimpleVector {
    std::vector<T> data_;
public:
    void push(T val) { data_.push_back(std::move(val)); }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        pointer ptr_;
        explicit Iterator(pointer p) : ptr_(p) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        Iterator& operator++() { ++ptr_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; }
    };

    Iterator begin() const { return Iterator(data_.data()); }
    Iterator end() const { return Iterator(data_.data() + data_.size()); }
};

int main() {
    SimpleVector<std::string> fruits;
    fruits.push("Apple");
    fruits.push("Banana");
    fruits.push("Cherry");

    std::cout << "Range-for loop over custom collection:\n";
    for (const auto& f : fruits) {
        std::cout << " - " << f << "\n";
    }
    return 0;
}
