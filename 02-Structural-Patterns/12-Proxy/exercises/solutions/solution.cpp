#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual std::string query(const std::string& sql) = 0;
};

class RealDatabase : public IDatabase {
public:
    int actual_db_calls = 0;
    std::string query(const std::string& sql) override {
        ++actual_db_calls;
        return "RESULT_FOR(" + sql + ")";
    }
};

class CachedDatabaseProxy : public IDatabase {
    std::shared_ptr<RealDatabase> real_db_;
    std::unordered_map<std::string, std::string> cache_;
public:
    explicit CachedDatabaseProxy(std::shared_ptr<RealDatabase> db) : real_db_(std::move(db)) {}

    std::string query(const std::string& sql) override {
        auto it = cache_.find(sql);
        if (it != cache_.end()) {
            return it->second;
        }
        std::string res = real_db_->query(sql);
        cache_[sql] = res;
        return res;
    }
};

int main() {
    auto real_db = std::make_shared<RealDatabase>();
    CachedDatabaseProxy proxy(real_db);

    std::string r1 = proxy.query("SELECT * FROM users;");
    std::string r2 = proxy.query("SELECT * FROM users;");

    assert(r1 == "RESULT_FOR(SELECT * FROM users;)");
    assert(r2 == "RESULT_FOR(SELECT * FROM users;)");
    assert(real_db->actual_db_calls == 1); // Second query answered by cache!

    std::cout << "Proxy solution verified successfully!\n";
    return 0;
}
