// 03-real-world-example.cpp: Text Editor Character Glyph Flyweights
#include <iostream>
#include <unordered_map>

class Glyph {
    char c_;
public:
    explicit Glyph(char c) : c_(c) {}
    void render(int fontSize) const { std::cout << c_ << " (size: " << fontSize << ") "; }
};

class GlyphPool {
    std::unordered_map<char, Glyph> pool_;
public:
    const Glyph& get(char c) {
        if (pool_.find(c) == pool_.end()) pool_.emplace(c, Glyph(c));
        return pool_.at(c);
    }
};

int main() {
    GlyphPool pool;
    pool.get('A').render(12);
    pool.get('B').render(14);
    pool.get('A').render(16);
    std::cout << "\n";
    return 0;
}
