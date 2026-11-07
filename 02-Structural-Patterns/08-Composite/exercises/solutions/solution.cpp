#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class IOrgComponent {
public:
    virtual ~IOrgComponent() = default;
    virtual double get_salary() const = 0;
    virtual size_t get_headcount() const = 0;
};

class IndividualContributor : public IOrgComponent {
    std::string name_;
    double salary_;
public:
    IndividualContributor(std::string name, double salary)
        : name_(std::move(name)), salary_(salary) {}

    double get_salary() const override { return salary_; }
    size_t get_headcount() const override { return 1; }
};

class Department : public IOrgComponent {
    std::string dept_name_;
    std::vector<std::shared_ptr<IOrgComponent>> members_;
public:
    explicit Department(std::string name) : dept_name_(std::move(name)) {}

    void add(std::shared_ptr<IOrgComponent> member) {
        members_.push_back(std::move(member));
    }

    double get_salary() const override {
        double total = 0.0;
        for (const auto& m : members_) total += m->get_salary();
        return total;
    }

    size_t get_headcount() const override {
        size_t count = 0;
        for (const auto& m : members_) count += m->get_headcount();
        return count;
    }
};

int main() {
    auto eng = std::make_shared<Department>("Engineering");
    eng->add(std::make_shared<IndividualContributor>("Alice", 120000.0));
    eng->add(std::make_shared<IndividualContributor>("Bob", 110000.0));

    auto product = std::make_shared<Department>("Product");
    product->add(std::make_shared<IndividualContributor>("Charlie", 130000.0));

    auto company = std::make_shared<Department>("Company");
    company->add(eng);
    company->add(product);

    assert(company->get_headcount() == 3);
    assert(company->get_salary() == 360000.0);

    std::cout << "Composite solution verified successfully!\n";
    return 0;
}
