#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IChatRoom;

class User {
    std::string name_;
    IChatRoom* room_;
public:
    User(std::string name, IChatRoom* room) : name_(std::move(name)), room_(room) {}
    // TODO: send(msg) and receive(sender, msg)
};

class IChatRoom {
public:
    virtual ~IChatRoom() = default;
    virtual void broadcast(const std::string& sender, const std::string& msg) = 0;
};

// TODO: Implement ConcreteChatRoom

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
