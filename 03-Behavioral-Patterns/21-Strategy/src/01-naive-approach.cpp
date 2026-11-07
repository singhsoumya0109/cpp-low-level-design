#include <iostream>
#include <string>

// Naive Approach: Monster if-else branching on algorithm type
// Violates Open/Closed Principle
enum class RouteMode { WALKING, DRIVING, BICYCLING };

class Navigator {
public:
    void build_route(RouteMode mode, const std::string& from, const std::string& to) {
        if (mode == RouteMode::WALKING) {
            std::cout << "[Walking Route] Calculating shortest pedestrian paths from " << from << " to " << to << "\n";
        } else if (mode == RouteMode::DRIVING) {
            std::cout << "[Driving Route] Calculating fastest highways with live traffic from " << from << " to " << to << "\n";
        } else if (mode == RouteMode::BICYCLING) {
            std::cout << "[Bicycling Route] Finding designated bike lanes from " << from << " to " << to << "\n";
        }
    }
};

int main() {
    Navigator nav;
    nav.build_route(RouteMode::WALKING, "Central Park", "Times Square");
    nav.build_route(RouteMode::DRIVING, "Airport", "Downtown Hotel");
    return 0;
}
