#include <iostream>
#include <memory>
#include <string>

// Real-world: TCP Connection State Machine
class TCPConnection;

class ITCPState {
public:
    virtual ~ITCPState() = default;
    virtual void open(TCPConnection&) { std::cout << "Invalid in current state.\n"; }
    virtual void close(TCPConnection&) { std::cout << "Invalid in current state.\n"; }
    virtual void acknowledge(TCPConnection&) { std::cout << "Invalid in current state.\n"; }
    virtual std::string name() const = 0;
};

class TCPConnection {
    std::unique_ptr<ITCPState> state_;
public:
    explicit TCPConnection(std::unique_ptr<ITCPState> s) : state_(std::move(s)) {}
    void change_state(std::unique_ptr<ITCPState> s) { state_ = std::move(s); }
    void open() { state_->open(*this); }
    void close() { state_->close(*this); }
    void ack() { state_->acknowledge(*this); }
    std::string current_state() const { return state_->name(); }
};

class TCPEstablished : public ITCPState {
public:
    void close(TCPConnection& conn) override;
    std::string name() const override { return "ESTABLISHED"; }
};

class TCPListen : public ITCPState {
public:
    void open(TCPConnection& conn) override {
        std::cout << "[TCP Listen] Received SYN -> moving to ESTABLISHED\n";
        conn.change_state(std::make_unique<TCPEstablished>());
    }
    std::string name() const override { return "LISTEN"; }
};

class TCPClosed : public ITCPState {
public:
    void open(TCPConnection& conn) override {
        std::cout << "[TCP Closed] Opening socket -> moving to LISTEN\n";
        conn.change_state(std::make_unique<TCPListen>());
    }
    std::string name() const override { return "CLOSED"; }
};

void TCPEstablished::close(TCPConnection& conn) {
    std::cout << "[TCP Established] Sending FIN -> moving to CLOSED\n";
    conn.change_state(std::make_unique<TCPClosed>());
}

int main() {
    TCPConnection conn(std::make_unique<TCPClosed>());
    std::cout << "State: " << conn.current_state() << "\n";

    conn.open();
    std::cout << "State: " << conn.current_state() << "\n";

    conn.open();
    std::cout << "State: " << conn.current_state() << "\n";

    conn.close();
    std::cout << "State: " << conn.current_state() << "\n";
    return 0;
}
