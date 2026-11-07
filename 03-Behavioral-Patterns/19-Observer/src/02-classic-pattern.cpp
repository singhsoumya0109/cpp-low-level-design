#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(float temperature, float humidity) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
};

class WeatherData : public ISubject {
    std::vector<std::weak_ptr<IObserver>> observers_;
    float temp_ = 0.0f;
    float humidity_ = 0.0f;
public:
    void set_measurements(float t, float h) {
        temp_ = t;
        humidity_ = h;
        notify();
    }

    void attach(std::shared_ptr<IObserver> observer) override {
        observers_.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver> observer) override {
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                [&](const std::weak_ptr<IObserver>& w) {
                    auto sp = w.lock();
                    return !sp || sp == observer;
                }),
            observers_.end());
    }

    void notify() override {
        for (auto it = observers_.begin(); it != observers_.end(); ) {
            if (auto sp = it->lock()) {
                sp->update(temp_, humidity_);
                ++it;
            } else {
                it = observers_.erase(it); // Cleanup dead observer
            }
        }
    }
};

class CurrentConditionsDisplay : public IObserver {
public:
    void update(float temperature, float humidity) override {
        std::cout << "[Current Conditions] Temp: " << temperature << " C, Humidity: " << humidity << "%\n";
    }
};

int main() {
    auto weather_data = std::make_shared<WeatherData>();
    auto display = std::make_shared<CurrentConditionsDisplay>();

    weather_data->attach(display);
    weather_data->set_measurements(26.2f, 65.0f);
    weather_data->set_measurements(28.0f, 70.0f);
    return 0;
}
