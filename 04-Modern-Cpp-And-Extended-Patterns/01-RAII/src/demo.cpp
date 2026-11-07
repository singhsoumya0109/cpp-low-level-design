#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <stdexcept>

// Generic ScopeGuard for executing cleanup actions upon exiting scope
template <typename F>
class ScopeGuard {
public:
    explicit ScopeGuard(F cleanup) : cleanup_(std::move(cleanup)), active_(true) {}
    ~ScopeGuard() {
        if (active_) {
            cleanup_();
        }
    }
    // Non-copyable
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    // Movable
    ScopeGuard(ScopeGuard&& other) noexcept : cleanup_(std::move(other.cleanup_)), active_(other.active_) {
        other.active_ = false;
    }

    void dismiss() noexcept { active_ = false; }

private:
    F cleanup_;
    bool active_;
};

template <typename F>
ScopeGuard<F> make_scope_guard(F cleanup) {
    return ScopeGuard<F>(std::move(cleanup));
}

// Simulated Resource Handle (e.g. File / Socket / Database lock)
class DatabaseConnection {
public:
    explicit DatabaseConnection(std::string conn_str) : conn_str_(std::move(conn_str)), is_open_(true) {
        std::cout << "[RAII] Connection opened: " << conn_str_ << "\n";
    }

    ~DatabaseConnection() {
        close();
    }

    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    DatabaseConnection(DatabaseConnection&& other) noexcept 
        : conn_str_(std::move(other.conn_str_)), is_open_(other.is_open_) {
        other.is_open_ = false;
    }

    DatabaseConnection& operator=(DatabaseConnection&& other) noexcept {
        if (this != &other) {
            close();
            conn_str_ = std::move(other.conn_str_);
            is_open_ = other.is_open_;
            other.is_open_ = false;
        }
        return *this;
    }

    void execute(const std::string& query) {
        if (!is_open_) throw std::runtime_error("Cannot execute on closed connection");
        std::cout << "[RAII] Executing: " << query << "\n";
    }

    void close() noexcept {
        if (is_open_) {
            std::cout << "[RAII] Connection safely closed: " << conn_str_ << "\n";
            is_open_ = false;
        }
    }

    bool is_open() const noexcept { return is_open_; }

private:
    std::string conn_str_;
    bool is_open_;
};

int main() {
    std::cout << "=== Modern C++ RAII & ScopeGuard Demo ===\n";
    {
        DatabaseConnection conn("db://localhost:5432/orders");
        conn.execute("SELECT * FROM orders WHERE status = 'PENDING';");

        bool rollback_needed = true;
        auto guard = make_scope_guard([&]() {
            if (rollback_needed) {
                std::cout << "[ScopeGuard] Rollback executed automatically on exit\n";
            }
        });

        // Simulate successful completion:
        rollback_needed = false;
        guard.dismiss(); // dismiss rollback
        std::cout << "[RAII] Transaction committed, guard dismissed\n";
    } // conn destructor runs here deterministically
    return 0;
}
