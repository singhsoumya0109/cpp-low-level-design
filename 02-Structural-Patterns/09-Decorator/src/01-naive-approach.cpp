#include <iostream>

// Naive Approach: Subclass explosion for every combination of condiments
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual double cost() const = 0;
};

class Espresso : public Beverage {
public:
    double cost() const override { return 2.00; }
};

class EspressoWithMilk : public Beverage {
public:
    double cost() const override { return 2.50; }
};

class EspressoWithMilkAndSugar : public Beverage {
public:
    double cost() const override { return 2.75; }
};

class EspressoWithMilkAndSugarAndCaramel : public Beverage {
public:
    double cost() const override { return 3.25; }
};

int main() {
    EspressoWithMilkAndSugar drink;
    std::cout << "Cost: $" << drink.cost() << "\n";
    return 0;
}
