// 02-classic-pattern.cpp: Home Theater Facade
#include <iostream>
#include <memory>

class Amplifier { public: void on() { std::cout << "Amp on\n"; } void off() { std::cout << "Amp off\n"; } };
class Projector { public: void on() { std::cout << "Projector on\n"; } void off() { std::cout << "Projector off\n"; } };
class Lights { public: void dim() { std::cout << "Lights dimmed 10%\n"; } void brighten() { std::cout << "Lights 100%\n"; } };

class HomeTheaterFacade {
private:
    Amplifier amp_;
    Projector projector_;
    Lights lights_;
public:
    void watchMovie() {
        std::cout << "--- Starting Movie Night ---\n";
        lights_.dim();
        projector_.on();
        amp_.on();
    }
    void endMovie() {
        std::cout << "--- Ending Movie ---\n";
        amp_.off();
        projector_.off();
        lights_.brighten();
    }
};

int main() {
    HomeTheaterFacade theater;
    theater.watchMovie();
    theater.endMovie();
    return 0;
}
