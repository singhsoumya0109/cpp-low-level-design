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

// TODO: Implement IndividualContributor and DepartmentComposite

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
