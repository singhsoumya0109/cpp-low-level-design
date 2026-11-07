#include <iostream>
#include <vector>
#include <string>

// Naive Approach: Storing duplicate heavy intrinsic data inside every individual particle
struct HeavyParticle {
    int x, y; // 8 bytes extrinsic
    std::vector<char> heavy_sprite_data; // 100 KB intrinsic redundant per particle!
};

int main() {
    std::vector<HeavyParticle> particles;
    // Allocating 10,000 particles with individual 100KB buffers = ~1 GB memory consumption!
    std::cout << "Naive particles consume massive memory for duplicate sprite data.\n";
    return 0;
}
