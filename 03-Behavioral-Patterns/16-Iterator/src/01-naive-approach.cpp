#include <iostream>
#include <vector>

// Naive Approach: Exposing internal storage directly to clients
class SecretRegistry {
public:
    std::vector<int> internal_data{10, 20, 30, 40};
    // Client directly accesses internal container; cannot change internal structure without breaking callers
};

int main() {
    SecretRegistry reg;
    for (size_t i = 0; i < reg.internal_data.size(); ++i) {
        std::cout << reg.internal_data[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
