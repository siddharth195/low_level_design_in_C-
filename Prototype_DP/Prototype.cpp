class Shape {
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;  // Abstract method to demonstrate the shape
};

#include <iostream>
#include <memory>

// Circle.h
class Circle : public Shape {
public:
    Circle(int radius) : radius_(radius) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

    void draw() const override {
        std::cout << "Drawing a Circle with radius " << radius_ << std::endl;
    }

private:
    int radius_;
};

// Rectangle.h
class Rectangle : public Shape {
public:
    Rectangle(int width, int height) : width_(width), height_(height) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width " << width_ << " and height " << height_ << std::endl;
    }

private:
    int width_;
    int height_;
};


int main() {
    // Create original objects
    std::unique_ptr<Shape> originalCircle = std::make_unique<Circle>(10);
    std::unique_ptr<Shape> originalRectangle = std::make_unique<Rectangle>(20, 30);

    // Clone the objects
    std::unique_ptr<Shape> clonedCircle = originalCircle->clone();
    std::unique_ptr<Shape> clonedRectangle = originalRectangle->clone();

    // Use the objects
    std::cout << "Original Circle: ";
    originalCircle->draw();
   
    std::cout << "Cloned Circle: ";
    clonedCircle->draw();

    std::cout << "Original Rectangle: ";
    originalRectangle->draw();
    
    std::cout << "Cloned Rectangle: ";
    clonedRectangle->draw();

    return 0;
}
