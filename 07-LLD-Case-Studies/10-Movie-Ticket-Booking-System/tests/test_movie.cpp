#include <cassert>
#include <iostream>

enum class SeatState { FREE, RESERVED };

class Theater {
    SeatState seats_[10] = {SeatState::FREE};
public:
    bool reserve(int i) {
        if (i >= 0 && i < 10 && seats_[i] == SeatState::FREE) {
            seats_[i] = SeatState::RESERVED;
            return true;
        }
        return false;
    }
};

int main() {
    std::cout << "[TEST] Running Movie Booking tests...\n";
    Theater t;
    assert(t.reserve(0));
    assert(!t.reserve(0)); // Double booking prevented
    assert(t.reserve(1));
    std::cout << "[TEST] All Movie Booking tests PASSED!\n";
    return 0;
}
