#include <iostream>
#include <memory>
#include <vector>
#include <string>

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool has_next() const = 0;
    virtual T next() = 0;
};

template <typename T>
class Container {
public:
    virtual ~Container() = default;
    virtual std::unique_ptr<Iterator<T>> create_iterator() const = 0;
};

class NameRepository : public Container<std::string> {
    std::vector<std::string> names_;
public:
    void add(std::string name) { names_.push_back(std::move(name)); }

    class NameIterator : public Iterator<std::string> {
        const std::vector<std::string>& data_;
        size_t index_ = 0;
    public:
        explicit NameIterator(const std::vector<std::string>& d) : data_(d) {}
        bool has_next() const override { return index_ < data_.size(); }
        std::string next() override { return data_[index_++]; }
    };

    std::unique_ptr<Iterator<std::string>> create_iterator() const override {
        return std::make_unique<NameIterator>(names_);
    }
};

int main() {
    NameRepository repo;
    repo.add("Alice");
    repo.add("Bob");
    repo.add("Charlie");

    auto it = repo.create_iterator();
    while (it->has_next()) {
        std::cout << "Name: " << it->next() << "\n";
    }
    return 0;
}
