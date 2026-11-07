#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

struct HttpRequest {
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

class Middleware {
protected:
    std::shared_ptr<Middleware> next_;
public:
    virtual ~Middleware() = default;

    std::shared_ptr<Middleware> link_with(std::shared_ptr<Middleware> next) {
        next_ = std::move(next);
        return next_;
    }

    virtual bool check(const HttpRequest& req) {
        if (next_) {
            return next_->check(req);
        }
        return true;
    }
};

class AuthMiddleware : public Middleware {
public:
    bool check(const HttpRequest& req) override {
        auto it = req.headers.find("Authorization");
        if (it == req.headers.end() || it->second != "Bearer secret_token") {
            std::cout << "[AuthMiddleware] Unauthorized request to " << req.path << "\n";
            return false;
        }
        std::cout << "[AuthMiddleware] Auth token verified\n";
        return Middleware::check(req);
    }
};

class RateLimitMiddleware : public Middleware {
    int max_requests_;
    int count_ = 0;
public:
    explicit RateLimitMiddleware(int max_reqs) : max_requests_(max_reqs) {}

    bool check(const HttpRequest& req) override {
        if (++count_ > max_requests_) {
            std::cout << "[RateLimitMiddleware] Rate limit exceeded\n";
            return false;
        }
        std::cout << "[RateLimitMiddleware] Request allowed (" << count_ << "/" << max_requests_ << ")\n";
        return Middleware::check(req);
    }
};

int main() {
    auto auth = std::make_shared<AuthMiddleware>();
    auto ratelimit = std::make_shared<RateLimitMiddleware>(2);
    auth->link_with(ratelimit);

    HttpRequest valid_req{"/api/data", {{"Authorization", "Bearer secret_token"}}, "{}"};
    HttpRequest invalid_req{"/api/data", {}, "{}"};

    std::cout << "Testing invalid request:\n";
    auth->check(invalid_req);

    std::cout << "\nTesting valid requests:\n";
    auth->check(valid_req);
    auth->check(valid_req);
    auth->check(valid_req); // Trigger rate limit
    return 0;
}
