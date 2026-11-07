#include <iostream>

// Naive Approach: Monster switch-case state machine
enum class PlayerState { STOPPED, PLAYING, PAUSED };

class MusicPlayer {
    PlayerState state_ = PlayerState::STOPPED;
public:
    void play() {
        switch (state_) {
            case PlayerState::STOPPED:
                std::cout << "Starting playback from beginning\n";
                state_ = PlayerState::PLAYING;
                break;
            case PlayerState::PLAYING:
                std::cout << "Already playing\n";
                break;
            case PlayerState::PAUSED:
                std::cout << "Resuming playback\n";
                state_ = PlayerState::PLAYING;
                break;
        }
    }

    void pause() {
        switch (state_) {
            case PlayerState::STOPPED:
                std::cout << "Cannot pause when stopped\n";
                break;
            case PlayerState::PLAYING:
                std::cout << "Pausing playback\n";
                state_ = PlayerState::PAUSED;
                break;
            case PlayerState::PAUSED:
                std::cout << "Already paused\n";
                break;
        }
    }
};

int main() {
    MusicPlayer mp;
    mp.play();
    mp.pause();
    mp.play();
    return 0;
}
