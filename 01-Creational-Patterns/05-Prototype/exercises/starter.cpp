#include <iostream>
#include <memory>
#include <string>

class Monster {
public:
    virtual ~Monster() = default;
    virtual std::unique_ptr<Monster> clone() const = 0;
    virtual std::string describe() const = 0;
};

// TODO: Implement Goblin and Dragon with health, attack, and clone()

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
