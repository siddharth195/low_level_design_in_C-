#include <string>
#include <vector>
#include <iostream>

class Meal {
public:
    void addItem(const std::string& item) {
        items_.emplace_back(item);
    }

    void showItems() const {
        for (const auto& item : items_) {
            std::cout << item << std::endl;
        }
    }

private:
    std::vector<std::string> items_;
};

class MealBuilder {
public:
    virtual ~MealBuilder() = default;
    virtual void buildBurger() = 0;
    virtual void buildDrink() = 0;
    virtual Meal getMeal() = 0;
};


class VegMealBuilder : public MealBuilder {
public:
    void buildBurger() override {
        meal_.addItem("Veg Burger");
    }

    void buildDrink() override {
        meal_.addItem("Coke");
    }

    Meal getMeal() override {
        return meal_;
    }

private:
    Meal meal_;
};

class NonVegMealBuilder : public MealBuilder {
public:
    void buildBurger() override {
        meal_.addItem("Chicken Burger");
    }

    void buildDrink() override {
        meal_.addItem("Pepsi");
    }

    Meal getMeal() override {
        return meal_;
    }

private:
    Meal meal_;
};


class MealDirector {
public:
    void setBuilder(MealBuilder* builder) {
        builder_ = builder;
    }

    Meal constructMeal() {
        builder_->buildBurger();
        builder_->buildDrink();
        return builder_->getMeal();
    }

private:
    MealBuilder* builder_;
};

int main() {
    // Create builder objects
    VegMealBuilder vegBuilder;
    NonVegMealBuilder nonVegBuilder;

    // Create director object
    MealDirector director;

    // Construct a VegMeal
    director.setBuilder(&vegBuilder);
    Meal vegMeal = director.constructMeal();

    std::cout << "Veg Meal:" << std::endl;
    vegMeal.showItems();

    std::cout << std::endl;

    // Construct a NonVegMeal
    director.setBuilder(&nonVegBuilder);
    Meal nonVegMeal = director.constructMeal();

    std::cout << "Non-Veg Meal:" << std::endl;
    nonVegMeal.showItems();

    return 0;
}


