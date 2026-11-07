#include <iostream>
#include <vector>
#include <functional>
#include <string>

// Modern C++17 Pipeline / Chain of Responsibility using functional closures
struct Context {
    std::string user;
    bool is_authenticated = false;
    bool is_admin = false;
    std::string response;

    explicit Context(std::string u) : user(std::move(u)) {}
};

using Filter = std::function<bool(Context&)>;

class RequestPipeline {
    std::vector<Filter> filters_;
public:
    RequestPipeline& use(Filter filter) {
        filters_.push_back(std::move(filter));
        return *this;
    }

    bool execute(Context& ctx) const {
        for (const auto& filter : filters_) {
            if (!filter(ctx)) {
                return false; // Intercepted and halted
            }
        }
        return true;
    }
};

int main() {
    RequestPipeline pipeline;

    // Filter 1: Authentication
    pipeline.use([](Context& ctx) {
        if (ctx.user.empty()) {
            ctx.response = "401 Unauthorized";
            return false;
        }
        ctx.is_authenticated = true;
        return true;
    });

    // Filter 2: Authorization
    pipeline.use([](Context& ctx) {
        if (ctx.user != "admin") {
            ctx.response = "403 Forbidden";
            return false;
        }
        ctx.is_admin = true;
        return true;
    });

    // Filter 3: Business handler
    pipeline.use([](Context& ctx) {
        ctx.response = "200 OK: Welcome, Admin!";
        return true;
    });

    Context guest{""};
    pipeline.execute(guest);
    std::cout << "Guest response: " << guest.response << "\n";

    Context normal_user{"john_doe"};
    pipeline.execute(normal_user);
    std::cout << "Normal user response: " << normal_user.response << "\n";

    Context admin{"admin"};
    pipeline.execute(admin);
    std::cout << "Admin response: " << admin.response << "\n";

    return 0;
}
