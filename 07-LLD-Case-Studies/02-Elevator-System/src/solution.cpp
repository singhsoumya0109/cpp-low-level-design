#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <mutex>
#include <memory>

enum class Direction { UP, DOWN, IDLE };
enum class DoorState { OPEN, CLOSED };

class ElevatorCar {
    int id_;
    int current_floor_ = 1;
    Direction direction_ = Direction::IDLE;
    DoorState door_ = DoorState::CLOSED;
    std::set<int> up_destinations_;
    std::set<int> down_destinations_;
    mutable std::mutex mtx_;

public:
    explicit ElevatorCar(int id) : id_(id) {}

    void add_destination(int floor) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (floor > current_floor_) {
            up_destinations_.insert(floor);
            if (direction_ == Direction::IDLE) direction_ = Direction::UP;
        } else if (floor < current_floor_) {
            down_destinations_.insert(floor);
            if (direction_ == Direction::IDLE) direction_ = Direction::DOWN;
        }
    }

    void step() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (direction_ == Direction::UP) {
            if (!up_destinations_.empty()) {
                auto next_stop = *up_destinations_.begin();
                current_floor_ = next_stop;
                up_destinations_.erase(next_stop);
                door_ = DoorState::OPEN;
                std::cout << "[Car " << id_ << "] Arrived at floor " << current_floor_ << " (Doors OPEN)\n";
                door_ = DoorState::CLOSED;
            }
            if (up_destinations_.empty()) {
                direction_ = down_destinations_.empty() ? Direction::IDLE : Direction::DOWN;
            }
        } else if (direction_ == Direction::DOWN) {
            if (!down_destinations_.empty()) {
                auto next_stop = *down_destinations_.rbegin();
                current_floor_ = next_stop;
                down_destinations_.erase(next_stop);
                door_ = DoorState::OPEN;
                std::cout << "[Car " << id_ << "] Arrived at floor " << current_floor_ << " (Doors OPEN)\n";
                door_ = DoorState::CLOSED;
            }
            if (down_destinations_.empty()) {
                direction_ = up_destinations_.empty() ? Direction::IDLE : Direction::UP;
            }
        }
    }

    int current_floor() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return current_floor_;
    }

    Direction direction() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return direction_;
    }

    int id() const { return id_; }
};

class ElevatorController {
    std::vector<std::shared_ptr<ElevatorCar>> cars_;
public:
    explicit ElevatorController(int num_cars) {
        for (int i = 1; i <= num_cars; ++i) {
            cars_.push_back(std::make_shared<ElevatorCar>(i));
        }
    }

    void request_pickup(int floor) {
        // Dispatcher: Assign to nearest idle or moving toward car
        std::shared_ptr<ElevatorCar> best_car = cars_[0];
        int min_dist = 10000;
        for (const auto& car : cars_) {
            int dist = std::abs(car->current_floor() - floor);
            if (dist < min_dist) {
                min_dist = dist;
                best_car = car;
            }
        }
        std::cout << "[Dispatcher] Assigning floor " << floor << " to Car #" << best_car->id() << "\n";
        best_car->add_destination(floor);
    }

    void step_all() {
        for (auto& car : cars_) car->step();
    }
};

int main() {
    std::cout << "=== Elevator System Simulation ===\n";
    ElevatorController controller(2);

    controller.request_pickup(5);
    controller.request_pickup(3);

    controller.step_all();
    controller.step_all();
    return 0;
}
