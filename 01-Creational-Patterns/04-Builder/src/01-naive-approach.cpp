// 01-naive-approach.cpp: Telescoping Constructor Anti-Pattern
#include <iostream>
#include <string>

class HttpResponse {
public:
    int status_;
    std::string body_;
    std::string contentType_;
    bool isGzip_;
    int timeoutMs_;

    // Telescoping constructors - error prone!
    HttpResponse(int status) : status_(status), contentType_("text/html"), isGzip_(false), timeoutMs_(5000) {}
    HttpResponse(int status, std::string body) : HttpResponse(status) { body_ = body; }
    HttpResponse(int status, std::string body, std::string type, bool gzip, int timeout)
        : status_(status), body_(body), contentType_(type), isGzip_(gzip), timeoutMs_(timeout) {}
};

int main() {
    HttpResponse res(200, "OK", "application/json", true, 3000);
    std::cout << "Status: " << res.status_ << "\n";
    return 0;
}
