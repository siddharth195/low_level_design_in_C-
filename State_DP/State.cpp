// State.h
class MediaPlayer;

class State {
public:
    virtual ~State() = default;
    virtual void play(MediaPlayer* player) = 0;
    virtual void pause(MediaPlayer* player) = 0;
    virtual void stop(MediaPlayer* player) = 0;
};


// MediaPlayer.h
#include <memory>
#include <iostream>
#include "State.h"

class MediaPlayer {
public:
    MediaPlayer();

    void setState(std::unique_ptr<State> state) {
        state_ = std::move(state);
    }

    void play() {
        if (state_) state_->play(this);
    }

    void pause() {
        if (state_) state_->pause(this);
    }

    void stop() {
        if (state_) state_->stop(this);
    }

private:
    std::unique_ptr<State> state_;
};

#include "State.h"
#include "MediaPlayer.h"

// PlayingState.h
class PlayingState : public State {
public:
    void play(MediaPlayer* player) override {
        std::cout << "Already playing." << std::endl;
    }

    void pause(MediaPlayer* player) override {
        std::cout << "Pausing playback." << std::endl;
        player->setState(std::make_unique<PausedState>());
    }

    void stop(MediaPlayer* player) override {
        std::cout << "Stopping playback." << std::endl;
        player->setState(std::make_unique<StoppedState>());
    }
};

// PausedState.h
class PausedState : public State {
public:
    void play(MediaPlayer* player) override {
        std::cout << "Resuming playback." << std::endl;
        player->setState(std::make_unique<PlayingState>());
    }

    void pause(MediaPlayer* player) override {
        std::cout << "Already paused." << std::endl;
    }

    void stop(MediaPlayer* player) override {
        std::cout << "Stopping playback." << std::endl;
        player->setState(std::make_unique<StoppedState>());
    }
};

// StoppedState.h
class StoppedState : public State {
public:
    void play(MediaPlayer* player) override {
        std::cout << "Starting playback." << std::endl;
        player->setState(std::make_unique<PlayingState>());
    }

    void pause(MediaPlayer* player) override {
        std::cout << "Cannot pause. The player is stopped." << std::endl;
    }

    void stop(MediaPlayer* player) override {
        std::cout << "Already stopped." << std::endl;
    }
};

#include "MediaPlayer.h"
#include "PlayingState.h"
#include "PausedState.h"
#include "StoppedState.h"

int main() {
    // Create MediaPlayer and set initial state to Stopped
    MediaPlayer player;
    player.setState(std::make_unique<StoppedState>());

    // Interact with MediaPlayer
    player.play();  // Starting playback.
    player.pause(); // Pausing playback.
    player.play();  // Resuming playback.
    player.stop();  // Stopping playback.
    player.stop();  // Already stopped.

    return 0;
}


