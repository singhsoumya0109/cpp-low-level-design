#include <cassert>
#include <iostream>
#include <vector>
#include <string>

class Notifier {
public:
    std::vector<std::string> log;
    void send(const std::string& dest, const std::string& m) { log.push_back(dest + ":" + m); }
};

int main() {
    std::cout << "[TEST] Running Notification tests...\n";
    Notifier n;
    n.send("dev@test.com", "Build Succeeded");
    assert(n.log.size() == 1);
    assert(n.log[0] == "dev@test.com:Build Succeeded");
    std::cout << "[TEST] All Notification tests PASSED!\n";
    return 0;
}
