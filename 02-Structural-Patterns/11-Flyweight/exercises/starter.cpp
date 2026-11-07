#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct TextStyle {
    std::string font;
    int size;
    std::string color;
};

// TODO: Implement TextStyleFactory to return shared instances of TextStyle
// TODO: Implement CharacterGlyph storing char + shared_ptr<TextStyle>

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
