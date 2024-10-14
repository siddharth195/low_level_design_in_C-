// Observer.h
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature) = 0;
};
// subscriberin
#include <vector>
#include <memory>

// Subject.h
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
};

// WeatherStation.h
class WeatherStation : public Subject {
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers_.emplace_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void notify() override {
        for (const auto& observer : observers_) {
            observer->update(temperature_);
        }
    }

    void setTemperature(float temperature) { 
        temperature_ = temperature;
        notify();
    }

private:
    float temperature_;
    std::vector<std::shared_ptr<Observer>> observers_;
};

// TemperatureDisplay.h
class TemperatureDisplay : public Observer {
public:
    void update(float temperature) override {
        std::cout << "TemperatureDisplay: Temperature updated to " << temperature << " degrees." << std::endl;
    }
};

// FanController.h
class FanController : public Observer {
public:
    void update(float temperature) override {
        if (temperature > 25.0f) {
            std::cout << "FanController: It's hot! Turning on the fan." << std::endl;
        } else {
            std::cout << "FanController: The temperature is fine. Turning off the fan." << std::endl;
        }
    }
};

#include "WeatherStation.h"
#include "TemperatureDisplay.h"
#include "FanController.h"

int main() {
    // Create the subject
    std::shared_ptr<WeatherStation> weatherStation = std::make_shared<WeatherStation>(); 

    // Create observers
    std::shared_ptr<Observer> tempDisplay = std::make_shared<TemperatureDisplay>();
    std::shared_ptr<Observer> fanControl = std::make_shared<FanController>();

    // Attach observers to the subject
    weatherStation->attach(tempDisplay);
    weatherStation->attach(fanControl);

    // Update the subject's state
    weatherStation->setTemperature(28.0f); 
    weatherStation->setTemperature(22.0f);

    // Detach an observer and update the subject's state again
    weatherStation->detach(tempDisplay);
    weatherStation->setTemperature(30.0f);

    return 0;
}
