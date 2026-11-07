#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

using Context = std::unordered_set<std::string>;

class IBoolExpr {
public:
    virtual ~IBoolExpr() = default;
    virtual bool eval(const Context& ctx) const = 0;
};

// TODO: Implement Literal(bool), FeatureFlag(string), AndExpr, NotExpr

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
