#include <cassert>
#include <iostream>
#include <vector>

class NumberSequence {
    std::vector<int> numbers_{1, 2, 3, 4, 5};
public:
    auto begin() const { return numbers_.begin(); }
    auto end() const { return numbers_.end(); }
};

int main() {
    std::cout << "[TEST] Running Iterator tests...\n";
    NumberSequence seq;
    int sum = 0;
    for (int n : seq) sum += n;
    assert(sum == 15);
    std::cout << "[TEST] All Iterator tests PASSED!\n";
    return 0;
}
