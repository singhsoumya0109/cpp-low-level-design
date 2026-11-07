#include <cassert>
#include <iostream>
#include <vector>
#include <string>

class BeverageMaker {
public:
    virtual ~BeverageMaker() = default;

    std::vector<std::string> prepare_recipe() {
        std::vector<std::string> log;
        log.push_back("BOIL_WATER");
        log.push_back(brew());
        log.push_back("POUR_IN_CUP");
        log.push_back(add_condiments());
        return log;
    }

protected:
    virtual std::string brew() = 0;
    virtual std::string add_condiments() = 0;
};

class Tea : public BeverageMaker {
protected:
    std::string brew() override { return "STEEP_TEA_BAG"; }
    std::string add_condiments() override { return "ADD_LEMON"; }
};

class Coffee : public BeverageMaker {
protected:
    std::string brew() override { return "DRIP_COFFEE"; }
    std::string add_condiments() override { return "ADD_SUGAR_AND_MILK"; }
};

int main() {
    Tea tea;
    auto tea_steps = tea.prepare_recipe();
    assert(tea_steps.size() == 4);
    assert(tea_steps[1] == "STEEP_TEA_BAG");
    assert(tea_steps[3] == "ADD_LEMON");

    Coffee coffee;
    auto coffee_steps = coffee.prepare_recipe();
    assert(coffee_steps[1] == "DRIP_COFFEE");
    assert(coffee_steps[3] == "ADD_SUGAR_AND_MILK");

    std::cout << "Template Method solution verified successfully!\n";
    return 0;
}
