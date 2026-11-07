#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <optional>
#include <unordered_map>

enum class VehicleType { MOTORCYCLE, CAR, TRUCK };
enum class SpotType { SMALL, COMPACT, LARGE };

struct Vehicle { std::string plate; VehicleType type; };
struct Spot { int id; SpotType type; bool occupied = false; };
struct Ticket { std::string id; int spot_id; };

class ParkingLot {
    std::mutex mtx_;
    std::vector<Spot> spots_;
    std::unordered_map<std::string, Ticket> tickets_;
    int ctr = 0;
public:
    void add_spot(int id, SpotType t) { spots_.push_back({id, t, false}); }
    std::optional<Ticket> park(const Vehicle& v) {
        std::lock_guard<std::mutex> lk(mtx_);
        for (auto& s : spots_) {
            if (!s.occupied) {
                if (v.type == VehicleType::CAR && s.type == SpotType::SMALL) continue;
                if (v.type == VehicleType::TRUCK && s.type != SpotType::LARGE) continue;
                s.occupied = true;
                Ticket t{"T" + std::to_string(++ctr), s.id};
                tickets_[t.id] = t;
                return t;
            }
        }
        return std::nullopt;
    }
    bool vacate(const std::string& tid) {
        std::lock_guard<std::mutex> lk(mtx_);
        auto it = tickets_.find(tid);
        if (it == tickets_.end()) return false;
        for (auto& s : spots_) {
            if (s.id == it->second.spot_id) { s.occupied = false; break; }
        }
        tickets_.erase(it);
        return true;
    }
    size_t free_spots() {
        std::lock_guard<std::mutex> lk(mtx_);
        size_t c = 0; for (auto& s : spots_) if (!s.occupied) ++c; return c;
    }
};

int main() {
    std::cout << "[TEST] Running Parking Lot tests...\n";
    ParkingLot lot;
    lot.add_spot(1, SpotType::SMALL);
    lot.add_spot(2, SpotType::COMPACT);

    assert(lot.free_spots() == 2);
    auto t1 = lot.park({"CAR-1", VehicleType::CAR});
    assert(t1.has_value());
    assert(t1->spot_id == 2); // Placed in compact, not small
    assert(lot.free_spots() == 1);

    bool ok = lot.vacate(t1->id);
    assert(ok);
    assert(lot.free_spots() == 2);

    std::cout << "[TEST] All Parking Lot tests PASSED!\n";
    return 0;
}
