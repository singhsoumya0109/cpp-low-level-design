#include <iostream>
#include <functional>
#include <vector>
#include <numeric>

// Modern C++17 Strategy using std::function & lambdas
using SortStrategy = std::function<void(std::vector<int>&)>;

class DataProcessor {
public:
    static void process(std::vector<int>& data, SortStrategy sorter) {
        sorter(data);
    }
};

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};

    // Strategy 1: Ascending sort
    DataProcessor::process(numbers, [](std::vector<int>& v) {
        std::sort(v.begin(), v.end(), std::less<int>());
    });
    std::cout << "Ascending: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    // Strategy 2: Descending sort
    DataProcessor::process(numbers, [](std::vector<int>& v) {
        std::sort(v.begin(), v.end(), std::greater<int>());
    });
    std::cout << "Descending: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
