#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

class SimpleFS {
    std::unordered_map<std::string, std::string> files;
public:
    void write(const std::string& path, const std::string& data) { files[path] = data; }
    std::string read(const std::string& path) const {
        auto it = files.find(path);
        return it != files.end() ? it->second : "";
    }
    bool exists(const std::string& path) const { return files.count(path) > 0; }
};

int main() {
    std::cout << "[TEST] Running File System tests...\n";
    SimpleFS fs;
    fs.write("/etc/hosts", "127.0.0.1 localhost");
    assert(fs.exists("/etc/hosts"));
    assert(fs.read("/etc/hosts") == "127.0.0.1 localhost");
    std::cout << "[TEST] All File System tests PASSED!\n";
    return 0;
}
