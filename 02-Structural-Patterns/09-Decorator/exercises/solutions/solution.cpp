#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class IDataSource {
public:
    virtual ~IDataSource() = default;
    virtual std::string process(const std::string& data) = 0;
};

class PlainTextSource : public IDataSource {
public:
    std::string process(const std::string& data) override {
        return data;
    }
};

class DataSourceDecorator : public IDataSource {
protected:
    std::unique_ptr<IDataSource> wrappee_;
public:
    explicit DataSourceDecorator(std::unique_ptr<IDataSource> source)
        : wrappee_(std::move(source)) {}
};

class UpperCaseDecorator : public DataSourceDecorator {
public:
    using DataSourceDecorator::DataSourceDecorator;
    std::string process(const std::string& data) override {
        std::string inner = wrappee_->process(data);
        for (char& c : inner) c = static_cast<char>(std::toupper(c));
        return inner;
    }
};

class BracketDecorator : public DataSourceDecorator {
public:
    using DataSourceDecorator::DataSourceDecorator;
    std::string process(const std::string& data) override {
        return "[" + wrappee_->process(data) + "]";
    }
};

int main() {
    auto pipeline = std::make_unique<BracketDecorator>(
        std::make_unique<UpperCaseDecorator>(
            std::make_unique<PlainTextSource>()
        )
    );

    std::string res = pipeline->process("hello world");
    assert(res == "[HELLO WORLD]");

    std::cout << "Decorator solution verified successfully!\n";
    return 0;
}
