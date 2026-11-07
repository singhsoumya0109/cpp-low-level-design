#include <iostream>
#include <memory>
#include <string>

class IDataSource {
public:
    virtual ~IDataSource() = default;
    virtual std::string write_data(const std::string& data) = 0;
};

// TODO: Implement SimpleDataSource, DataSourceDecorator, Base64Decorator, TimestampDecorator

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
