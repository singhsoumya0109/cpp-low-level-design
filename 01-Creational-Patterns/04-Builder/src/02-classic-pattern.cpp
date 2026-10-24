// 02-classic-pattern.cpp: Classic GoF Builder with Director
#include <iostream>
#include <string>
#include <memory>

class Computer {
public:
    std::string cpu_;
    std::string ram_;
    std::string gpu_;
    void specs() const {
        std::cout << "Computer Specs -> CPU: " << cpu_ << " | RAM: " << ram_ << " | GPU: " << gpu_ << "\n";
    }
};

class IComputerBuilder {
public:
    virtual ~IComputerBuilder() = default;
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildGPU() = 0;
    virtual std::unique_ptr<Computer> getResult() = 0;
};

class GamingComputerBuilder : public IComputerBuilder {
private:
    std::unique_ptr<Computer> comp_{std::make_unique<Computer>()};
public:
    void buildCPU() override { comp_->cpu_ = "Intel Core i9-14900K"; }
    void buildRAM() override { comp_->ram_ = "64GB DDR5 6000MHz"; }
    void buildGPU() override { comp_->gpu_ = "NVIDIA RTX 4090"; }
    std::unique_ptr<Computer> getResult() override { return std::move(comp_); }
};

class Director {
public:
    void constructGamingPC(IComputerBuilder& builder) {
        builder.buildCPU();
        builder.buildRAM();
        builder.buildGPU();
    }
};

int main() {
    Director director;
    GamingComputerBuilder builder;
    director.constructGamingPC(builder);
    auto pc = builder.getResult();
    pc->specs();
    return 0;
}
