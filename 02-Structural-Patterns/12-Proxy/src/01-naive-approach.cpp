#include <iostream>
#include <string>

// Naive Approach: Immediately downloading heavy 50MB image in constructor
// even if the user never renders it in the GUI
class HeavyImage {
    std::string filename_;
public:
    explicit HeavyImage(std::string filename) : filename_(std::move(filename)) {
        std::cout << "[HeavyImage] Downloading 50MB file over network: " << filename_ << "...\n";
    }
    void render() {
        std::cout << "[HeavyImage] Rendering: " << filename_ << "\n";
    }
};

int main() {
    // Eager initialization of 10 images wastes network bandwidth and freezes GUI:
    HeavyImage img1("pic1.raw");
    HeavyImage img2("pic2.raw");
    return 0;
}
