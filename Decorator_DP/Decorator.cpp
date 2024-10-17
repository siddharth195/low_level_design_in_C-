// Coffee.h
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};


#include <string>

// SimpleCoffee.h
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 5.0;
    }
};



// CoffeeDecorator.h
class CoffeeDecorator : public Coffee {
public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee_(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee_->getDescription();
    }

    double cost() const override {
        return coffee_->cost();
    }

protected:
    std::unique_ptr<Coffee> coffee_;
};


// MilkDecorator.h
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + ", Milk";
    }

    double cost() const override {
        return coffee_->cost() + 1.5;
    }
};

// SugarDecorator.h
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + ", Sugar";
    }

    double cost() const override {
        return coffee_->cost() + 0.5;
    }
};

// CaramelDecorator.h
class CaramelDecorator : public CoffeeDecorator {
public:
    CaramelDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + ", Caramel";
    }

    double cost() const override {
        return coffee_->cost() + 2.0;
    }
};

#include "SimpleCoffee.h"
#include "MilkDecorator.h"
#include "SugarDecorator.h"
#include "CaramelDecorator.h"
#include <iostream>

int main() {
    // Create a simple coffee
    std::unique_ptr<Coffee> myCoffee = std::make_unique<SimpleCoffee>();

    std::cout << "Plain coffee: " << myCoffee->getDescription() << ", Cost: $" << myCoffee->cost() << std::endl;

    // Add milk
    myCoffee = std::make_unique<MilkDecorator>(std::move(myCoffee));
    std::cout << "With milk: " << myCoffee->getDescription() << ", Cost: $" << myCoffee->cost() << std::endl;

    // Add sugar
    myCoffee = std::make_unique<SugarDecorator>(std::move(myCoffee));
    std::cout << "With sugar: " << myCoffee->getDescription() << ", Cost: $" << myCoffee->cost() << std::endl;

    // Add caramel
    myCoffee = std::make_unique<CaramelDecorator>(std::move(myCoffee));
    std::cout << "With caramel: " << myCoffee->getDescription() << ", Cost: $" << myCoffee->cost() << std::endl;

    return 0;
}



