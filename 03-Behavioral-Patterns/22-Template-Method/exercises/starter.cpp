#include <iostream>
#include <string>

class BeverageMaker {
public:
    virtual ~BeverageMaker() = default;
    void prepare_recipe() {
        // TODO: boil_water, brew, pour_in_cup, add_condiments
    }
    // TODO: declare hooks
};

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
