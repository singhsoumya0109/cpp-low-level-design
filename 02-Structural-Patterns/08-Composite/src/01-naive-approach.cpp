#include <iostream>
#include <vector>
#include <string>

// Naive Approach: Rigid separation between File and Folder
// Leads to duplicated traversal loops and inability to treat them uniformly
class File {
public:
    std::string name;
    size_t size;
    File(std::string n, size_t s) : name(std::move(n)), size(s) {}
};

class Directory {
public:
    std::string name;
    std::vector<File> files;
    std::vector<Directory> subdirs;

    Directory(std::string n) : name(std::move(n)) {}

    size_t calculate_total_size() const {
        size_t total = 0;
        for (const auto& f : files) total += f.size;
        for (const auto& d : subdirs) total += d.calculate_total_size();
        return total;
    }
};

int main() {
    Directory root("root");
    root.files.emplace_back("readme.txt", 100);

    Directory sub("docs");
    sub.files.emplace_back("spec.pdf", 500);
    root.subdirs.push_back(sub);

    std::cout << "Total size: " << root.calculate_total_size() << " bytes\n";
    return 0;
}
