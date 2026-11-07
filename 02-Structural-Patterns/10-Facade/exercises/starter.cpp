#include <iostream>
#include <string>

// Subsystems
class AudioEngine { public: bool init() { return true; } };
class VideoEngine { public: bool init() { return true; } };
class CodecManager { public: bool load_file(const std::string&) { return true; } };

// TODO: Implement MediaPlayerFacade with play(const std::string& filename)

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
