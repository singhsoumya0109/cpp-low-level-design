#include <iostream>

// Naive Approach: Client directly initializes and couples to 4 intricate subsystem APIs
class AudioDriver { public: void init() { std::cout << "Audio initialized\n"; } };
class VideoDecoder { public: void load() { std::cout << "Video loaded\n"; } };
class SubtitleEngine { public: void sync() { std::cout << "Subtitles synced\n"; } };
class NetworkStream { public: void connect() { std::cout << "Stream connected\n"; } };

int main() {
    // Client has to know every low-level API call and exact ordering
    AudioDriver audio;
    audio.init();

    VideoDecoder video;
    video.load();

    SubtitleEngine subs;
    subs.sync();

    NetworkStream stream;
    stream.connect();

    std::cout << "Playback started\n";
    return 0;
}
