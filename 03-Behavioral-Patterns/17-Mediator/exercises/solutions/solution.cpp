#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IChatRoom;

class User {
    std::string name_;
    IChatRoom* room_;
public:
    std::vector<std::string> inbox;
    User(std::string name, IChatRoom* room) : name_(std::move(name)), room_(room) {}
    const std::string& name() const { return name_; }

    void send(const std::string& msg);
    void receive(const std::string& from, const std::string& msg) {
        inbox.push_back(from + ": " + msg);
    }
};

class IChatRoom {
public:
    virtual ~IChatRoom() = default;
    virtual void register_user(std::shared_ptr<User> user) = 0;
    virtual void broadcast(const std::string& sender, const std::string& msg) = 0;
};

class ChatRoom : public IChatRoom {
    std::vector<std::shared_ptr<User>> users_;
public:
    void register_user(std::shared_ptr<User> user) override {
        users_.push_back(std::move(user));
    }

    void broadcast(const std::string& sender, const std::string& msg) override {
        for (const auto& u : users_) {
            if (u->name() != sender) {
                u->receive(sender, msg);
            }
        }
    }
};

void User::send(const std::string& msg) {
    room_->broadcast(name_, msg);
}

int main() {
    auto room = std::make_shared<ChatRoom>();
    auto alice = std::make_shared<User>("Alice", room.get());
    auto bob = std::make_shared<User>("Bob", room.get());
    auto charlie = std::make_shared<User>("Charlie", room.get());

    room->register_user(alice);
    room->register_user(bob);
    room->register_user(charlie);

    alice->send("Hello everyone!");

    assert(alice->inbox.empty());
    assert(bob->inbox.size() == 1);
    assert(bob->inbox[0] == "Alice: Hello everyone!");
    assert(charlie->inbox.size() == 1);
    assert(charlie->inbox[0] == "Alice: Hello everyone!");

    std::cout << "Mediator solution verified successfully!\n";
    return 0;
}
