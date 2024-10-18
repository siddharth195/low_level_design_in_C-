#include <iostream>

// TV.h
class TV {
public:
    void on_tv() {
        std::cout << "Turning on the TV." << std::endl;
    }
    void off() {
        std::cout << "Turning off the TV." << std::endl;
    }
    void setInput(const std::string& input) {
        std::cout << "Setting TV input to " << input << std::endl;
    }
};

// DVDPlayer.h
class DVDPlayer {
public:
    void on() {
        std::cout << "Turning on the DVD player." << std::endl;
    }
    void off() {
        std::cout << "Turning off the DVD player." << std::endl;
    }
    void play(const std::string& movie) {
        std::cout << "Playing movie: " << movie << std::endl;
    }
};

// SoundSystem.h
class SoundSystem {
public:
    void on() {
        std::cout << "Turning on the sound system." << std::endl;
    }
    void off() {
        std::cout << "Turning off the sound system." << std::endl;
    }
    void setVolume(int volume) {
        std::cout << "Setting sound system volume to " << volume << std::endl;
    }
};

#include <memory>
#include <string>
#include "TV.h"
#include "DVDPlayer.h"
#include "SoundSystem.h"

// HomeTheaterFacade.h
class HomeTheaterFacade {
public:
    HomeTheaterFacade(std::shared_ptr<TV> tv, std::shared_ptr<DVDPlayer> dvdPlayer, std::shared_ptr<SoundSystem> soundSystem)
        : tv_(tv), dvdPlayer_(dvdPlayer), soundSystem_(soundSystem) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie..." << std::endl;
        tv_->on();
        tv_->setInput("DVD");
        dvdPlayer_->on();
        dvdPlayer_->play(movie);
        soundSystem_->on();
        soundSystem_->setVolume(20);
    }

    void endMovie() {
        std::cout << "Shutting down the home theater..." << std::endl;
        dvdPlayer_->off();
        tv_->off();
        soundSystem_->off();
    }

private:
    std::shared_ptr<TV> tv_;
    std::shared_ptr<DVDPlayer> dvdPlayer_;
    std::shared_ptr<SoundSystem> soundSystem_;
};

int main() {
    // Create subsystem components
    std::shared_ptr<TV> tv = std::make_shared<TV>();
    std::shared_ptr<DVDPlayer> dvdPlayer = std::make_shared<DVDPlayer>();
    std::shared_ptr<SoundSystem> soundSystem = std::make_shared<SoundSystem>();

    // Create the Facade
    HomeTheaterFacade homeTheater(tv, dvdPlayer, soundSystem);

    // Use the Facade to watch a movie
    homeTheater.watchMovie("Inception");

    std::cout << std::endl;

    // Use the Facade to end the movie
    homeTheater.endMovie();

    return 0;
}

