// 02-classic-pattern.cpp: Object Adapter in Modern C++
#include <iostream>
#include <memory>

class IJsonData {
public:
    virtual ~IJsonData() = default;
    virtual void readJson() const = 0;
};

class LegacyXmlService {
public:
    void fetchXml() const { std::cout << "<xml><data>Payload</data></xml>\n"; }
};

// Object Adapter wraps Adaptee
class XmlToJsonAdapter : public IJsonData {
private:
    std::unique_ptr<LegacyXmlService> xmlService_;
public:
    explicit XmlToJsonAdapter(std::unique_ptr<LegacyXmlService> xml) : xmlService_(std::move(xml)) {}
    void readJson() const override {
        std::cout << "[Adapter] Translating XML to JSON format...\n";
        xmlService_->fetchXml();
        std::cout << "{\"data\": \"Payload\"}\n";
    }
};

int main() {
    std::unique_ptr<IJsonData> jsonClient = std::make_unique<XmlToJsonAdapter>(std::make_unique<LegacyXmlService>());
    jsonClient->readJson();
    return 0;
}
