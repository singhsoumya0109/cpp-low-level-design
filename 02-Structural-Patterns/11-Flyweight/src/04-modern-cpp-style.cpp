// 04-modern-cpp-style.cpp: Flyweight using string_view symbol intern pool
#include <iostream>
#include <string_view>
#include <unordered_set>

class SymbolTable {
    std::unordered_set<std::string> symbols_;
public:
    std::string_view intern(const std::string& s) {
        return *symbols_.insert(s).first;
    }
};

int main() {
    SymbolTable tbl;
    auto s1 = tbl.intern("identifier_name");
    auto s2 = tbl.intern("identifier_name");
    std::cout << "Identical address: " << (s1.data() == s2.data() ? "YES" : "NO") << "\n";
    return 0;
}
