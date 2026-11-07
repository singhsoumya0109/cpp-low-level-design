#include <iostream>
#include <string>
#include <unordered_map>

class HttpRequest {
public:
    std::string method;
    std::string url;
    std::string body;
    int timeout_ms = 5000;
    std::unordered_map<std::string, std::string> headers;
};

// TODO: Implement HttpRequestBuilder with fluent methods
// .set_method(m).set_url(u).add_header(k, v).set_body(b).set_timeout(ms).build()

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
