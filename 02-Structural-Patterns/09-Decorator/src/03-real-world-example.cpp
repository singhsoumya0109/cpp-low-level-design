// 03-real-world-example.cpp: Stream Compression and Encryption Decorator
#include <iostream>
#include <memory>
#include <string>

class IDataStream {
public:
    virtual ~IDataStream() = default;
    virtual void write(const std::string& data) const = 0;
};

class FileDataStream : public IDataStream {
public:
    void write(const std::string& data) const override {
        std::cout << "Writing raw bytes to disk: " << data << "\n";
    }
};

class StreamDecorator : public IDataStream {
protected:
    std::unique_ptr<IDataStream> stream_;
public:
    explicit StreamDecorator(std::unique_ptr<IDataStream> s) : stream_(std::move(s)) {}
};

class EncryptDecorator : public StreamDecorator {
public:
    using StreamDecorator::StreamDecorator;
    void write(const std::string& data) const override {
        std::cout << "[AES-256 Encrypting payload...]\n";
        stream_->write("[ENCRYPTED:" + data + "]");
    }
};

int main() {
    std::unique_ptr<IDataStream> s = std::make_unique<FileDataStream>();
    s = std::make_unique<EncryptDecorator>(std::move(s));
    s->write("Confidential Token");
    return 0;
}
