#include <iostream>
#include <memory>
#include <string>

class IRouteStrategy {
public:
    virtual ~IRouteStrategy() = default;
    virtual void calculate_route(const std::string& from, const std::string& to) const = 0;
};

class WalkingStrategy : public IRouteStrategy {
public:
    void calculate_route(const std::string& from, const std::string& to) const override {
        std::cout << "[Walking] Walking paths & trails: " << from << " -> " << to << "\n";
    }
};

class DrivingStrategy : public IRouteStrategy {
public:
    void calculate_route(const std::string& from, const std::string& to) const override {
        std::cout << "[Driving] Highway with live congestion: " << from << " -> " << to << "\n";
    }
};

class Navigator {
    std::unique_ptr<IRouteStrategy> strategy_;
public:
    explicit Navigator(std::unique_ptr<IRouteStrategy> s) : strategy_(std::move(s)) {}
    void set_strategy(std::unique_ptr<IRouteStrategy> s) { strategy_ = std::move(s); }
    void plan_route(const std::string& from, const std::string& to) const {
        if (strategy_) strategy_->calculate_route(from, to);
    }
};

int main() {
    Navigator nav(std::make_unique<WalkingStrategy>());
    nav.plan_route("Home", "Coffee Shop");

    nav.set_strategy(std::make_unique<DrivingStrategy>());
    nav.plan_route("Home", "Office");
    return 0;
}
