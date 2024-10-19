// Command.h
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
};

// Light.h
#include <iostream>

class Light {
public:
    void on() const {
        std::cout << "Light is On" << std::endl;
    }
    
    void off() const {
        std::cout << "Light is Off" << std::endl;
    }
};

// GarageDoor.h
class GarageDoor {
public:
    void open() const {
        std::cout << "Garage Door is Open" << std::endl;
    }
    
    void close() const {
        std::cout << "Garage Door is Closed" << std::endl;
    }
};

// LightOnCommand.h
class LightOnCommand : public Command {
public:
    explicit LightOnCommand(const Light& light) : light_(light) {}
    
    void execute() const override {
        light_.on();
    }
    
private:
    const Light& light_;
};

// LightOffCommand.h
class LightOffCommand : public Command {
public:
    explicit LightOffCommand(const Light& light) : light_(light) {}
    
    void execute() const override {
        light_.off();
    }
    
private:
    const Light& light_;
};

// GarageDoorOpenCommand.h
class GarageDoorOpenCommand : public Command {
public:
    explicit GarageDoorOpenCommand(const GarageDoor& garageDoor) : garageDoor_(garageDoor) {}
    
    void execute() const override {
        garageDoor_.open();
    }
    
private:
    const GarageDoor& garageDoor_;
};

// GarageDoorCloseCommand.h
class GarageDoorCloseCommand : public Command {
public:
    explicit GarageDoorCloseCommand(const GarageDoor& garageDoor) : garageDoor_(garageDoor) {}
    
    void execute() const override {
        garageDoor_.close();
    }
    
private:
    const GarageDoor& garageDoor_;
};

#include <memory>
#include <vector>

// RemoteControl.h
class RemoteControl {
public:
    void setCommand(std::unique_ptr<Command> command) {
        commands_.push_back(std::move(command));
    }
    
    void pressButton() const {
        if (!commands_.empty()) {
            commands_.back()->execute();
        }
    }

private:
    std::vector<std::unique_ptr<Command>> commands_;
};

#include "Command.h"
#include "Light.h"
#include "GarageDoor.h"
#include "LightOnCommand.h"
#include "LightOffCommand.h"
#include "GarageDoorOpenCommand.h"
#include "GarageDoorCloseCommand.h"
#include "RemoteControl.h"

int main() {
    // Create receivers
    Light livingRoomLight;
    GarageDoor garageDoor;
    
    // Create commands
    std::unique_ptr<Command> lightOn = std::make_unique<LightOnCommand>(livingRoomLight);
    std::unique_ptr<Command> lightOff = std::make_unique<LightOffCommand>(livingRoomLight);
    std::unique_ptr<Command> garageOpen = std::make_unique<GarageDoorOpenCommand>(garageDoor);
    std::unique_ptr<Command> garageClose = std::make_unique<GarageDoorCloseCommand>(garageDoor);
    
    // Create invoker
    RemoteControl remote;
    
    // Execute commands
    remote.setCommand(std::move(lightOn));
    remote.pressButton(); // Light is On

    remote.setCommand(std::move(lightOff));
    remote.pressButton(); // Light is Off

    remote.setCommand(std::move(garageOpen));
    remote.pressButton(); // Garage Door is Open

    remote.setCommand(std::move(garageClose));
    remote.pressButton(); // Garage Door is Closed

    return 0;
}

