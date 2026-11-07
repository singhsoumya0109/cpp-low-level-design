#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Real-world: File Compression Engine
class ICompressionStrategy {
public:
    virtual ~ICompressionStrategy() = default;
    virtual std::vector<uint8_t> compress(const std::vector<uint8_t>& data) const = 0;
    virtual std::string algorithm_name() const = 0;
};

class GzipStrategy : public ICompressionStrategy {
public:
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data) const override {
        // High compression ratio simulation
        std::vector<uint8_t> out = data;
        out.resize(data.size() / 2);
        return out;
    }
    std::string algorithm_name() const override { return "GZIP (High ratio, moderate CPU)"; }
};

class SnappyStrategy : public ICompressionStrategy {
public:
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data) const override {
        // Fast compression simulation
        std::vector<uint8_t> out = data;
        out.resize(data.size() * 3 / 4);
        return out;
    }
    std::string algorithm_name() const override { return "Snappy (Ultra-fast, lower ratio)"; }
};

class FileArchiver {
    std::unique_ptr<ICompressionStrategy> compressor_;
public:
    explicit FileArchiver(std::unique_ptr<ICompressionStrategy> strat)
        : compressor_(std::move(strat)) {}

    void archive(const std::vector<uint8_t>& file_bytes) {
        std::cout << "[Archiver] Compressing " << file_bytes.size() << " bytes with "
                  << compressor_->algorithm_name() << "\n";
        auto compressed = compressor_->compress(file_bytes);
        std::cout << "[Archiver] Compressed output: " << compressed.size() << " bytes\n";
    }
};

int main() {
    std::vector<uint8_t> raw_log_data(1000, 0xAA);

    FileArchiver archiver(std::make_unique<SnappyStrategy>());
    archiver.archive(raw_log_data);

    archiver = FileArchiver(std::make_unique<GzipStrategy>());
    archiver.archive(raw_log_data);
    return 0;
}
