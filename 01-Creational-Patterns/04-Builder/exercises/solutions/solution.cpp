#include <iostream>
#include <string>
class SqlBuilder {
    std::string query_;
public:
    SqlBuilder& select(std::string c) { query_ += "SELECT " + c + " "; return *this; }
    SqlBuilder& from(std::string t) { query_ += "FROM " + t; return *this; }
    std::string build() { return query_; }
};
int main() { SqlBuilder b; std::cout << b.select("*").from("users").build() << "\n"; return 0; }
