// 02-classic-pattern.cpp: Beverage Decorator Pattern
#include <iostream>
#include <memory>
#include <string>

class IBeverage {
public:
    virtual ~IBeverage() = default;
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};

class Espresso : public IBeverage {
public:
    std::string getDescription() const override { return "Espresso"; }
    double cost() const override { return 1.99; }
};

// Decorator base class
class BeverageDecorator : public IBeverage {
protected:
    std::unique_ptr<IBeverage> beverage_;
public:
    explicit BeverageDecorator(std::unique_ptr<IBeverage> b) : beverage_(std::move(b)) {}
};

class MilkDecorator : public BeverageDecorator {
public:
    explicit MilkDecorator(std::unique_ptr<IBeverage> b) : BeverageDecorator(std::move(b)) {}
    std::string getDescription() const override { return beverage_->getDescription() + ", Steamed Milk"; }
    double cost() const override { return beverage_->cost() + 0.50; }
};

class CaramelDecorator : public BeverageDecorator {
public:
    explicit CaramelDecorator(std::unique_ptr<IBeverage> b) : BeverageDecorator(std::move(b)) {}
    std::string getDescription() const override { return beverage_->getDescription() + ", Caramel Drizzle"; }
    double cost() const override { return beverage_->cost() + 0.75; }
};

int main() {
    std::unique_ptr<IBeverage> order = std::make_unique<Espresso>();
    order = std::make_unique<MilkDecorator>(std::move(order));
    order = std::make_unique<CaramelDecorator>(std::move(order));

    std::cout << "Order: " << order->getDescription() << " | Cost: $" << order->cost() << "\n";
    return 0;
}
