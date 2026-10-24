// 02-classic-pattern.cpp: Virtual Proxy for Lazy Image Loading
#include <iostream>
#include <memory>
#include <string>

class IImage {
public:
    virtual ~IImage() = default;
    virtual void display() = 0;
};

class RealImage : public IImage {
private:
    std::string filename_;
    void loadFromDisk() { std::cout << "Loading 50MB file " << filename_ << " from disk...\n"; }
public:
    explicit RealImage(std::string filename) : filename_(std::move(filename)) {
        loadFromDisk();
    }
    void display() override { std::cout << "Rendering " << filename_ << "\n"; }
};

class ProxyImage : public IImage {
private:
    std::string filename_;
    std::unique_ptr<RealImage> realImage_{nullptr}; // Lazy loaded
public:
    explicit ProxyImage(std::string filename) : filename_(std::move(filename)) {}

    void display() override {
        if (!realImage_) {
            std::cout << "[Proxy] Initializing real image on first demand...\n";
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        realImage_->display();
    }
};

int main() {
    std::unique_ptr<IImage> img = std::make_unique<ProxyImage>("banner_4k.png");
    std::cout << "Proxy created; image not loaded into RAM yet.\n";
    img->display(); // Loads and renders
    img->display(); // Renders directly
    return 0;
}
