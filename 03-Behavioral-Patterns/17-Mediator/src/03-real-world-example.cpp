#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Real-world: Air Traffic Control (ATC) Tower Mediator
class Airplane;

class IAirTrafficControl {
public:
    virtual ~IAirTrafficControl() = default;
    virtual bool request_landing(Airplane* plane) = 0;
    virtual void notify_runway_cleared(Airplane* plane) = 0;
};

class Airplane {
    std::string callsign_;
    IAirTrafficControl* atc_;
public:
    Airplane(std::string callsign, IAirTrafficControl* atc)
        : callsign_(std::move(callsign)), atc_(atc) {}

    const std::string& get_callsign() const { return callsign_; }

    void land() {
        std::cout << "[" << callsign_ << "] Requesting landing permission...\n";
        if (atc_->request_landing(this)) {
            std::cout << "[" << callsign_ << "] Landing completed. Clearing runway.\n";
            atc_->notify_runway_cleared(this);
        } else {
            std::cout << "[" << callsign_ << "] Holding in airspace.\n";
        }
    }
};

class ATCTower : public IAirTrafficControl {
    bool runway_occupied_ = false;
    std::string current_landing_callsign_;
public:
    bool request_landing(Airplane* plane) override {
        if (!runway_occupied_) {
            runway_occupied_ = true;
            current_landing_callsign_ = plane->get_callsign();
            std::cout << "[ATC Tower] Cleared to land on Runway 27L: " << current_landing_callsign_ << "\n";
            return true;
        }
        std::cout << "[ATC Tower] Runway busy. Denied landing for " << plane->get_callsign() << "\n";
        return false;
    }

    void notify_runway_cleared(Airplane* plane) override {
        if (plane->get_callsign() == current_landing_callsign_) {
            runway_occupied_ = false;
            std::cout << "[ATC Tower] Runway 27L is now CLEARED by " << plane->get_callsign() << "\n";
        }
    }
};

int main() {
    ATCTower tower;
    Airplane flight1("UA819", &tower);
    Airplane flight2("DL404", &tower);

    flight1.land();
    flight2.land();
    return 0;
}
