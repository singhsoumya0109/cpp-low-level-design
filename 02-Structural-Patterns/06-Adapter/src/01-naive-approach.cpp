// 01-naive-approach.cpp: Incompatible interfaces directly coupled
#include <iostream>

class LegacyXmlParser {
public:
    void parseXml() { std::cout << "Parsing XML format data.\n"; }
};

int main() {
    LegacyXmlParser parser;
    parser.parseXml();
    return 0;
}
