// 03-real-world-example.cpp: Fluent HTTP Request Builder
#include <iostream>
#include <string>
#include <unordered_map>

class HttpRequest {
public:
    std::string url_;
    std::string method_;
    std::unordered_map<std::string, std::string> headers_;
    std::string body_;

    void print() const {
        std::cout << "[" << method_ << "] " << url_ << " (Body: " << body_ << ")\n";
    }
};

class HttpRequestBuilder {
private:
    HttpRequest request_;
public:
    HttpRequestBuilder() { request_.method_ = "GET"; }

    HttpRequestBuilder& url(std::string url) {
        request_.url_ = std::move(url);
        return *this;
    }
    HttpRequestBuilder& method(std::string method) {
        request_.method_ = std::move(method);
        return *this;
    }
    HttpRequestBuilder& header(std::string k, std::string v) {
        request_.headers_[std::move(k)] = std::move(v);
        return *this;
    }
    HttpRequestBuilder& body(std::string body) {
        request_.body_ = std::move(body);
        return *this;
    }

    HttpRequest build() {
        return std::move(request_);
    }
};

int main() {
    HttpRequest req = HttpRequestBuilder()
        .url("https://api.github.com/repos")
        .method("POST")
        .header("Authorization", "Bearer token_xyz")
        .body("{\"name\": \"cpp-low-level-design\"}")
        .build();
    req.print();
    return 0;
}
