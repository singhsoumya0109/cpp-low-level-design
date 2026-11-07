#include <cassert>
#include <iostream>
#include <string>

class AudioEngine {
public:
    bool is_ready = false;
    void init() { is_ready = true; }
};

class VideoEngine {
public:
    bool is_ready = false;
    void init() { is_ready = true; }
};

class CodecManager {
public:
    std::string current_file;
    bool load(const std::string& path) {
        current_file = path;
        return true;
    }
};

class MediaPlayerFacade {
    AudioEngine audio_;
    VideoEngine video_;
    CodecManager codec_;
public:
    bool play(const std::string& filepath) {
        audio_.init();
        video_.init();
        return codec_.load(filepath) && audio_.is_ready && video_.is_ready;
    }
};

int main() {
    MediaPlayerFacade player;
    assert(player.play("movie.mkv") == true);
    std::cout << "Facade solution verified successfully!\n";
    return 0;
}
