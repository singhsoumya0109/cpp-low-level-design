#include <iostream>
#include <string>

// Naive Approach: WeatherData is tightly coupled to concrete display boards
class PhoneDisplay {
public:
    void update(float temp) { std::cout << "[PhoneDisplay] Temp: " << temp << " C\n"; }
};

class WindowDisplay {
public:
    void update(float temp) { std::cout << "[WindowDisplay] Temp: " << temp << " C\n"; }
};

class WeatherStation {
    float temp_ = 0.0f;
    PhoneDisplay phone_;
    WindowDisplay window_;
public:
    void set_temperature(float t) {
        temp_ = t;
        // Adding a 3rd display requires modifying WeatherStation code!
        phone_.update(temp_);
        window_.update(temp_);
    }
};

int main() {
    WeatherStation ws;
    ws.set_temperature(24.5f);
    return 0;
}
