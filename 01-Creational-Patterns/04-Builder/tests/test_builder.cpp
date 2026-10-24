#include <cassert>
#include <iostream>
#include <string>

class Person {
public:
    std::string name_;
    int age_{0};
};

class PersonBuilder {
    Person p_;
public:
    PersonBuilder& name(std::string n) { p_.name_ = std::move(n); return *this; }
    PersonBuilder& age(int a) { p_.age_ = a; return *this; }
    Person build() { return std::move(p_); }
};

int main() {
    Person p = PersonBuilder().name("Alice").age(30).build();
    assert(p.name_ == "Alice");
    assert(p.age_ == 30);
    std::cout << "[TEST] ✓ Builder test passed!\n";
    return 0;
}
