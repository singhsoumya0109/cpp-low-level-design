#include <iostream>
#include <vector>
#include <string>

class Canvas {
    std::vector<std::string> shapes_;
public:
    void add_shape(std::string s) { shapes_.push_back(std::move(s)); }
    // TODO: Implement CanvasSnapshot token and save()/restore()
};

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
