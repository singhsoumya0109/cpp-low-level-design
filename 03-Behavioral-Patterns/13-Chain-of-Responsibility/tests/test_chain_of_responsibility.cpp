#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class Handler {
    std::shared_ptr<Handler> next_;
public:
    virtual ~Handler() = default;
    std::shared_ptr<Handler> set_next(std::shared_ptr<Handler> next) {
        next_ = std::move(next);
        return next_;
    }
    virtual int handle(int req) {
        if (next_) return next_->handle(req);
        return -1;
    }
};

class EvensHandler : public Handler {
public:
    int handle(int req) override {
        if (req % 2 == 0) return 2;
        return Handler::handle(req);
    }
};

class OddsHandler : public Handler {
public:
    int handle(int req) override {
        if (req % 2 != 0) return 1;
        return Handler::handle(req);
    }
};

int main() {
    std::cout << "[TEST] Running Chain of Responsibility tests...\n";

    auto h1 = std::make_shared<EvensHandler>();
    auto h2 = std::make_shared<OddsHandler>();
    h1->set_next(h2);

    assert(h1->handle(4) == 2);
    assert(h1->handle(7) == 1);

    std::cout << "[TEST] All Chain of Responsibility tests PASSED!\n";
    return 0;
}
