#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

class MiniSplitwise {
public:
    std::unordered_map<std::string, double> net; // positive means owed money
    void add_split(const std::string& payer, const std::string& payee, double amt) {
        net[payer] += amt;
        net[payee] -= amt;
    }
};

int main() {
    std::cout << "[TEST] Running Splitwise tests...\n";
    MiniSplitwise sw;
    sw.add_split("Alice", "Bob", 50.0);
    assert(sw.net["Alice"] == 50.0);
    assert(sw.net["Bob"] == -50.0);
    std::cout << "[TEST] All Splitwise tests PASSED!\n";
    return 0;
}
