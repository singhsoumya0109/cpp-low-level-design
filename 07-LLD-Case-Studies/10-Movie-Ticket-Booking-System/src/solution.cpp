#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <chrono>

enum class SeatStatus { AVAILABLE, LOCKED, BOOKED };

struct Seat {
    int id = 0;
    std::string row_col;
    SeatStatus status = SeatStatus::AVAILABLE;
    std::chrono::steady_clock::time_point lock_time{};

    Seat() = default;
    Seat(int i, std::string label) : id(i), row_col(std::move(label)) {}
};

class ShowBookingService {
    mutable std::mutex mtx_;
    std::unordered_map<int, Seat> seats_;
    const int lock_timeout_sec_ = 10;

public:
    void add_seat(int id, std::string label) {
        std::lock_guard<std::mutex> lock(mtx_);
        seats_[id] = Seat{id, std::move(label)};
    }

    bool lock_seat(int id) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = seats_.find(id);
        if (it == seats_.end()) return false;

        auto now = std::chrono::steady_clock::now();
        // Check if previously locked seat expired
        if (it->second.status == SeatStatus::LOCKED) {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.lock_time).count();
            if (elapsed > lock_timeout_sec_) {
                it->second.status = SeatStatus::AVAILABLE; // Expired lock
            }
        }

        if (it->second.status == SeatStatus::AVAILABLE) {
            it->second.status = SeatStatus::LOCKED;
            it->second.lock_time = now;
            std::cout << "[Booking] Seat " << it->second.row_col << " LOCKED for checkout.\n";
            return true;
        }
        return false;
    }

    bool confirm_booking(int id) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = seats_.find(id);
        if (it != seats_.end() && it->second.status == SeatStatus::LOCKED) {
            it->second.status = SeatStatus::BOOKED;
            std::cout << "[Booking] Seat " << it->second.row_col << " BOOKED successfully!\n";
            return true;
        }
        return false;
    }
};

int main() {
    std::cout << "=== Movie Ticket Booking Simulation ===\n";
    ShowBookingService svc;
    svc.add_seat(1, "A1");
    svc.add_seat(2, "A2");

    bool locked = svc.lock_seat(1);
    std::cout << "User 1 lock A1: " << (locked ? "SUCCESS" : "FAIL") << "\n";

    bool locked_again = svc.lock_seat(1);
    std::cout << "User 2 lock A1 (concurrent clash): " << (locked_again ? "SUCCESS" : "FAIL") << "\n";

    svc.confirm_booking(1);
    return 0;
}
