#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <chrono>
#include <optional>
#include <unordered_map>

enum class VehicleType { MOTORCYCLE, CAR, TRUCK };
enum class SpotType { SMALL, COMPACT, LARGE };

struct Vehicle {
    std::string license_plate;
    VehicleType type;
};

class ParkingSpot {
public:
    int id;
    int floor;
    SpotType type;
    bool is_occupied = false;
    std::string parked_license;

    ParkingSpot(int id, int floor, SpotType type)
        : id(id), floor(floor), type(type) {}

    bool can_fit(VehicleType vtype) const {
        if (vtype == VehicleType::MOTORCYCLE) return true;
        if (vtype == VehicleType::CAR) return type == SpotType::COMPACT || type == SpotType::LARGE;
        if (vtype == VehicleType::TRUCK) return type == SpotType::LARGE;
        return false;
    }
};

struct Ticket {
    std::string ticket_id;
    int spot_id;
    std::string license_plate;
    VehicleType vtype;
    std::chrono::system_clock::time_point entry_time;
};

class ParkingLot {
    mutable std::mutex mtx_;
    std::vector<ParkingSpot> spots_;
    std::unordered_map<std::string, Ticket> active_tickets_;
    int ticket_counter_ = 0;

public:
    void add_spot(int id, int floor, SpotType type) {
        std::lock_guard<std::mutex> lock(mtx_);
        spots_.emplace_back(id, floor, type);
    }

    std::optional<Ticket> park_vehicle(const Vehicle& v) {
        std::lock_guard<std::mutex> lock(mtx_);
        for (auto& spot : spots_) {
            if (!spot.is_occupied && spot.can_fit(v.type)) {
                spot.is_occupied = true;
                spot.parked_license = v.license_plate;

                Ticket t;
                t.ticket_id = "TICKET_" + std::to_string(++ticket_counter_);
                t.spot_id = spot.id;
                t.license_plate = v.license_plate;
                t.vtype = v.type;
                t.entry_time = std::chrono::system_clock::now();

                active_tickets_[t.ticket_id] = t;
                return t;
            }
        }
        return std::nullopt; // Lot full
    }

    double vacate_and_pay(const std::string& ticket_id, double hourly_rate = 10.0) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = active_tickets_.find(ticket_id);
        if (it == active_tickets_.end()) return -1.0;

        Ticket t = it->second;
        active_tickets_.erase(it);

        for (auto& spot : spots_) {
            if (spot.id == t.spot_id) {
                spot.is_occupied = false;
                spot.parked_license.clear();
                break;
            }
        }

        // Return flat hourly fee for demo
        double fee = hourly_rate;
        if (t.vtype == VehicleType::TRUCK) fee *= 2.0;
        else if (t.vtype == VehicleType::MOTORCYCLE) fee *= 0.5;
        return fee;
    }

    size_t available_spots() const {
        std::lock_guard<std::mutex> lock(mtx_);
        size_t count = 0;
        for (const auto& s : spots_) {
            if (!s.is_occupied) ++count;
        }
        return count;
    }
};

int main() {
    std::cout << "=== Parking Lot Simulation ===\n";
    ParkingLot lot;
    lot.add_spot(1, 1, SpotType::SMALL);
    lot.add_spot(2, 1, SpotType::COMPACT);
    lot.add_spot(3, 1, SpotType::LARGE);

    Vehicle bike{"BIKE-101", VehicleType::MOTORCYCLE};
    Vehicle car{"CAR-202", VehicleType::CAR};
    Vehicle truck{"TRUCK-303", VehicleType::TRUCK};

    auto t1 = lot.park_vehicle(bike);
    auto t2 = lot.park_vehicle(car);
    auto t3 = lot.park_vehicle(truck);

    std::cout << "Available spots: " << lot.available_spots() << "\n";

    if (t2) {
        double fee = lot.vacate_and_pay(t2->ticket_id);
        std::cout << "Car vacated. Fee: $" << fee << "\n";
    }

    std::cout << "Available spots: " << lot.available_spots() << "\n";
    return 0;
}
