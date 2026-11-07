#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct TextStyle {
    std::string font;
    int size;
};

class TextStyleFactory {
    std::unordered_map<std::string, std::shared_ptr<TextStyle>> pool_;
public:
    std::shared_ptr<TextStyle> get_style(const std::string& font, int size) {
        std::string key = font + "_" + std::to_string(size);
        auto it = pool_.find(key);
        if (it != pool_.end()) {
            return it->second;
        }
        auto style = std::make_shared<TextStyle>(TextStyle{font, size});
        pool_[key] = style;
        return style;
    }

    size_t unique_styles_count() const {
        return pool_.size();
    }
};

struct CharacterGlyph {
    char ch;
    std::shared_ptr<TextStyle> style;
};

int main() {
    TextStyleFactory factory;
    std::vector<CharacterGlyph> document;

    auto arial12 = factory.get_style("Arial", 12);

    for (int i = 0; i < 1000; ++i) {
        document.push_back(CharacterGlyph{'a', factory.get_style("Arial", 12)});
    }

    assert(document.size() == 1000);
    assert(factory.unique_styles_count() == 1);
    assert(document[0].style.get() == document[999].style.get());

    std::cout << "Flyweight solution verified successfully!\n";
    return 0;
}
