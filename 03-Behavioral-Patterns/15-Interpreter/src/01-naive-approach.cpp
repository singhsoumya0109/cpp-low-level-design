#include <iostream>
#include <string>

// Naive Approach: Ad-hoc character looping parser
// Breaks on nested brackets, variable precedence, and extensibility
int eval_simple_add(const std::string& expr) {
    int sum = 0;
    std::string cur;
    for (char c : expr) {
        if (c == '+') {
            sum += std::stoi(cur);
            cur.clear();
        } else if (c != ' ') {
            cur += c;
        }
    }
    if (!cur.empty()) sum += std::stoi(cur);
    return sum;
}

int main() {
    std::cout << "10 + 20 + 30 = " << eval_simple_add("10 + 20 + 30") << "\n";
    return 0;
}
