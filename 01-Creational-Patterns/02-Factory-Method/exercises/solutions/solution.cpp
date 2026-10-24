#include <iostream>
#include <memory>

class ITransport {
public:
    virtual ~ITransport() = default;
    virtual void deliver() const = 0;
};

class Truck : public ITransport {
public:
    void deliver() const override { std::cout << "Delivering by land in box.\n"; }
};

class Ship : public ITransport {
public:
    void deliver() const override { std::cout << "Delivering by sea in container.\n"; }
};

class Logistics {
public:
    virtual ~Logistics() = default;
    virtual std::unique_ptr<ITransport> createTransport() const = 0;
};

class RoadLogistics : public Logistics {
public:
    std::unique_ptr<ITransport> createTransport() const override { return std::make_unique<Truck>(); }
};

int main() {
    RoadLogistics road;
    auto t = road.createTransport();
    t->deliver();
    return 0;
}
