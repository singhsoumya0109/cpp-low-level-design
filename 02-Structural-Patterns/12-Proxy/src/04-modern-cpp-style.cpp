// 04-modern-cpp-style.cpp: Smart Reference Counting Caching Proxy
#include <iostream>
#include <memory>

class Service {
public:
    void run() const { std::cout << "Service executed.\n"; }
};

int main() {
    std::shared_ptr<Service> proxy = std::make_shared<Service>();
    proxy->run();
    return 0;
}
