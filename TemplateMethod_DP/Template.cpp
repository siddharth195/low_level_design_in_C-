// Beverage.h
#include <iostream>

class Beverage {
public:
    virtual ~Beverage() = default;

    // Template Method
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    virtual void brew() const = 0;              // Abstract method for brewing
    virtual void addCondiments() const = 0;     // Abstract method for adding condiments

    void boilWater() const {
        std::cout << "Boiling water" << std::endl;
    }

    void pourInCup() const {
        std::cout << "Pouring into cup" << std::endl;
    }
};

// Tea.h
class Tea : public Beverage {
protected:
    void brew() const override {
        std::cout << "Steeping the tea" << std::endl;
    }

    void addCondiments() const override {
        std::cout << "Adding lemon" << std::endl;
    }
};

// Coffee.h
class Coffee : public Beverage {
protected:
    void brew() const override {
        std::cout << "Dripping coffee through filter" << std::endl;
    }

    void addCondiments() const override {
        std::cout << "Adding sugar and milk" << std::endl;
    }
};

int main() {
    std::unique_ptr<Beverage> tea = std::make_unique<Tea>();
    std::unique_ptr<Beverage> coffee = std::make_unique<Coffee>();

    std::cout << "Preparing tea:\n";
    tea->prepareRecipe();
    std::cout << std::endl;

    std::cout << "Preparing coffee:\n";
    coffee->prepareRecipe();

    return 0;
}
