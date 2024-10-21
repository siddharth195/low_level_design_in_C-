// MediaPlayer.h
class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& filename) = 0;
};

#include <iostream>

// MP4Player.h
class MP4Player {
public:
    void playMP4(const std::string& filename) {
        std::cout << "Playing MP4 file: " << filename << std::endl;
    }
};

#include "MediaPlayer.h"
#include "MP4Player.h"

// MP4PlayerAdapter.h
class MP4PlayerAdapter : public MediaPlayer {
public:
    MP4PlayerAdapter(std::shared_ptr<MP4Player> player) : mp4Player_(player) {}

    void play(const std::string& filename) override {
        mp4Player_->playMP4(filename);
    }

private:
    std::shared_ptr<MP4Player> mp4Player_;
};

#include "MediaPlayer.h"
#include "MP4PlayerAdapter.h"

int main() {
    // Create an instance of MP4Player
    std::shared_ptr<MP4Player> mp4Player = std::make_shared<MP4Player>();

    // Create an adapter for MP4Player
    MP4PlayerAdapter adapter(mp4Player);

    // Use the adapter to play an MP4 file using the MediaPlayer interface
    adapter.play("example.mp4");

    return 0;
}

