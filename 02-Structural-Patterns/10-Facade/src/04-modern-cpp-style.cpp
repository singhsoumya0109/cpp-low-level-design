// 04-modern-cpp-style.cpp: Stateless static Facade with string_view
#include <iostream>
#include <string_view>

class OrderFacade {
public:
    static bool placeOrder(std::string_view userId, std::string_view itemId) {
        std::cout << "Validating user: " << userId << "\n";
        std::cout << "Reserving item: " << itemId << "\n";
        std::cout << "Dispatching order confirmation.\n";
        return true;
    }
};

int main() {
    OrderFacade::placeOrder("usr_101", "item_404");
    return 0;
}
