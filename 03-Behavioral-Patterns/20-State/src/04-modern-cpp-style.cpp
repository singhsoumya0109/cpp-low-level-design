#include <iostream>
#include <variant>
#include <string>

// Modern C++17 State Pattern using std::variant and std::visit
struct DisconnectedState {};
struct ConnectingState { int attempt = 1; };
struct ConnectedState { std::string session_token; };

using ConnectionState = std::variant<DisconnectedState, ConnectingState, ConnectedState>;

struct ConnectEvent {};
struct SuccessEvent { std::string token; };
struct DisconnectEvent {};

struct StateTransition {
    ConnectionState operator()(DisconnectedState, ConnectEvent) const {
        std::cout << "[Transition] Disconnected -> Connecting (Attempt 1)\n";
        return ConnectingState{1};
    }

    ConnectionState operator()(ConnectingState, SuccessEvent e) const {
        std::cout << "[Transition] Connecting -> Connected with token: " << e.token << "\n";
        return ConnectedState{std::move(e.token)};
    }

    ConnectionState operator()(ConnectedState, DisconnectEvent) const {
        std::cout << "[Transition] Connected -> Disconnected\n";
        return DisconnectedState{};
    }

    template <typename S, typename E>
    ConnectionState operator()(S current_state, E) const {
        std::cout << "[Transition] Ignored event in current state\n";
        return current_state;
    }
};

int main() {
    ConnectionState state = DisconnectedState{};

    state = std::visit([](auto s) { return StateTransition{}(s, ConnectEvent{}); }, state);
    state = std::visit([](auto s) { return StateTransition{}(s, SuccessEvent{"tok_abc123"}); }, state);
    state = std::visit([](auto s) { return StateTransition{}(s, DisconnectEvent{}); }, state);

    return 0;
}
