#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

struct User {
    std::string id;
    std::string name;
};

class SplitwiseService {
    // balances[A][B] = amount B owes A
    std::unordered_map<std::string, std::unordered_map<std::string, double>> balances_;

public:
    void add_equal_expense(const std::string& payer, double total_amount, const std::vector<std::string>& participants) {
        if (participants.empty()) return;
        double split_amount = total_amount / participants.size();

        for (const auto& participant : participants) {
            if (participant == payer) continue;
            // participant owes payer
            balances_[payer][participant] += split_amount;
            balances_[participant][payer] -= split_amount;
        }
    }

    void print_balances() const {
        std::cout << "--- Splitwise Net Balances ---\n";
        bool has_debts = false;
        for (const auto& [u1, owes_map] : balances_) {
            for (const auto& [u2, amt] : owes_map) {
                if (amt > 0.01) {
                    has_debts = true;
                    std::cout << u2 << " owes " << u1 << ": $" << std::fixed << std::setprecision(2) << amt << "\n";
                }
            }
        }
        if (!has_debts) std::cout << "All balances settled!\n";
    }

    double get_balance(const std::string& u1, const std::string& u2) const {
        auto it1 = balances_.find(u1);
        if (it1 != balances_.end()) {
            auto it2 = it1->second.find(u2);
            if (it2 != it1->second.end()) return it2->second;
        }
        return 0.0;
    }
};

int main() {
    std::cout << "=== Splitwise Simulation ===\n";
    SplitwiseService splitwise;

    // Alice pays $90 for Dinner with Alice, Bob, Charlie ($30 each)
    splitwise.add_equal_expense("Alice", 90.0, {"Alice", "Bob", "Charlie"});
    splitwise.print_balances();

    // Bob pays $60 for Taxi with Bob, Charlie ($30 each)
    splitwise.add_equal_expense("Bob", 60.0, {"Bob", "Charlie"});
    splitwise.print_balances();
    return 0;
}
