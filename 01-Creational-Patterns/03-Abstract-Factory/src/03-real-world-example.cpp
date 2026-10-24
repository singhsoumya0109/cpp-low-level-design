// 03-real-world-example.cpp: Multi-Cloud Storage and Compute Factory (AWS vs Azure)
#include <iostream>
#include <memory>
#include <string_view>

class IComputeInstance { public: virtual ~IComputeInstance() = default; virtual void start() const = 0; };
class IStorageBucket { public: virtual ~IStorageBucket() = default; virtual void upload(std::string_view file) const = 0; };

class AwsEC2 : public IComputeInstance { public: void start() const override { std::cout << "AWS EC2 instance starting.\n"; } };
class AwsS3 : public IStorageBucket { public: void upload(std::string_view file) const override { std::cout << "Uploading " << file << " to AWS S3.\n"; } };

class AzureVM : public IComputeInstance { public: void start() const override { std::cout << "Azure Virtual Machine starting.\n"; } };
class AzureBlob : public IStorageBucket { public: void upload(std::string_view file) const override { std::cout << "Uploading " << file << " to Azure Blob.\n"; } };

class ICloudFactory {
public:
    virtual ~ICloudFactory() = default;
    virtual std::unique_ptr<IComputeInstance> createCompute() const = 0;
    virtual std::unique_ptr<IStorageBucket> createStorage() const = 0;
};

class AwsFactory : public ICloudFactory {
public:
    std::unique_ptr<IComputeInstance> createCompute() const override { return std::make_unique<AwsEC2>(); }
    std::unique_ptr<IStorageBucket> createStorage() const override { return std::make_unique<AwsS3>(); }
};

int main() {
    std::unique_ptr<ICloudFactory> cloud = std::make_unique<AwsFactory>();
    auto server = cloud->createCompute();
    auto disk = cloud->createStorage();
    server->start();
    disk->upload("database.bak");
    return 0;
}
