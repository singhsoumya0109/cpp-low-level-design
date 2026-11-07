#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

class HttpRequest {
public:
    std::string method = "GET";
    std::string url;
    std::string body;
    int timeout_ms = 5000;
    std::unordered_map<std::string, std::string> headers;
};

class HttpRequestBuilder {
public:
    HttpRequestBuilder& set_method(std::string method) {
        request_.method = std::move(method);
        return *this;
    }

    HttpRequestBuilder& set_url(std::string url) {
        request_.url = std::move(url);
        return *this;
    }

    HttpRequestBuilder& add_header(std::string key, std::string value) {
        request_.headers[std::move(key)] = std::move(value);
        return *this;
    }

    HttpRequestBuilder& set_body(std::string body) {
        request_.body = std::move(body);
        return *this;
    }

    HttpRequestBuilder& set_timeout(int ms) {
        request_.timeout_ms = ms;
        return *this;
    }

    HttpRequest build() {
        if (request_.url.empty()) {
            throw std::runtime_error("URL must not be empty");
        }
        return std::move(request_);
    }

private:
    HttpRequest request_;
};

int main() {
    HttpRequest req = HttpRequestBuilder()
        .set_method("POST")
        .set_url("https://api.example.com/v1/orders")
        .add_header("Authorization", "Bearer token123")
        .set_body("{\"item\":\"widget\"}")
        .set_timeout(3000)
        .build();

    assert(req.method == "POST");
    assert(req.url == "https://api.example.com/v1/orders");
    assert(req.headers["Authorization"] == "Bearer token123");
    assert(req.body == "{\"item\":\"widget\"}");
    assert(req.timeout_ms == 3000);

    std::cout << "Builder solution verified successfully!\n";
    return 0;
}
