#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual std::string query(const std::string& sql) = 0;
};

// TODO: Implement RealDatabase (slow) and CachedDatabaseProxy (caches results)

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
