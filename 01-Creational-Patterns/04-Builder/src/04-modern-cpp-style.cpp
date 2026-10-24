// 04-modern-cpp-style.cpp: Step Builder Pattern enforcing compile-time validation
#include <iostream>
#include <string>

// Enforces order: url -> method -> build
class Request {
public:
    std::string url_;
    std::string method_;
};

class IMethodStep {
public:
    virtual ~IMethodStep() = default;
    virtual Request get() = 0;
    virtual Request post() = 0;
};

class IUrlStep {
public:
    virtual ~IUrlStep() = default;
    virtual IMethodStep& url(std::string u) = 0;
};

class StepBuilder : public IUrlStep, public IMethodStep {
private:
    Request req_;
public:
    IMethodStep& url(std::string u) override { req_.url_ = std::move(u); return *this; }
    Request get() override { req_.method_ = "GET"; return std::move(req_); }
    Request post() override { req_.method_ = "POST"; return std::move(req_); }

    static IUrlStep& create() {
        static StepBuilder b;
        return b;
    }
};

int main() {
    Request r = StepBuilder::create().url("https://example.com").get();
    std::cout << "Method: " << r.method_ << " | URL: " << r.url_ << "\n";
    return 0;
}
