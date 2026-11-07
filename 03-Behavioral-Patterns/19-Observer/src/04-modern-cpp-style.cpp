#include <iostream>
#include <functional>
#include <string>
#include <vector>

// Modern C++17 Functional Signal-Slot / Observer
template <typename... Args>
class Signal {
public:
    using Slot = std::function<void(Args...)>;

    void connect(Slot slot) {
        slots_.push_back(std::move(slot));
    }

    void emit(Args... args) const {
        for (const auto& slot : slots_) {
            slot(args...);
        }
    }

private:
    std::vector<Slot> slots_;
};

int main() {
    Signal<const std::string&, double> on_price_changed;

    // Connect lambda slot 1: Logger
    on_price_changed.connect([](const std::string& symbol, double price) {
        std::cout << "[Logger] " << symbol << " is now $" << price << "\n";
    });

    // Connect lambda slot 2: Threshold Alert
    on_price_changed.connect([](const std::string& symbol, double price) {
        if (price > 1000.0) {
            std::cout << "[ALERT] " << symbol << " broke above $1000!\n";
        }
    });

    on_price_changed.emit("GOOG", 980.0);
    on_price_changed.emit("GOOG", 1025.0);
    return 0;
}
