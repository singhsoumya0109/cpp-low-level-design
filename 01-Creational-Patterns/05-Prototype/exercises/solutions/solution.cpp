#include <iostream>
#include <memory>
#include <vector>
class Packet {
public:
    std::vector<int> data_;
    std::unique_ptr<Packet> clone() const {
        auto p = std::make_unique<Packet>();
        p->data_ = this->data_;
        return p;
    }
};
int main() { Packet p; p.data_ = {1, 2, 3}; auto p2 = p.clone(); return 0; }
