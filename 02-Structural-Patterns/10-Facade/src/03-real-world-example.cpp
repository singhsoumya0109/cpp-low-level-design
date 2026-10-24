// 03-real-world-example.cpp: Video Conversion Pipeline Facade
#include <iostream>
#include <string_view>

class AudioCodecExtractor { public: void extract(std::string_view f) { std::cout << "Extracting audio from " << f << "\n"; } };
class VideoTranscoder { public: void transcode(std::string_view f) { std::cout << "Transcoding H264 to AV1 for " << f << "\n"; } };

class VideoConverterFacade {
    AudioCodecExtractor audio_;
    VideoTranscoder video_;
public:
    void convert(std::string_view filename) {
        audio_.extract(filename);
        video_.transcode(filename);
        std::cout << "Video conversion complete.\n";
    }
};

int main() {
    VideoConverterFacade converter;
    converter.convert("clip.mov");
    return 0;
}
