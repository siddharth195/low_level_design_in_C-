#include <iostream>

class Button {
public:
    virtual ~Button() = default;
    virtual void paint() const = 0;  // Abstract method
};

// Checkbox.h
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void paint() const = 0;  // Abstract method
};

// WindowsButton.h
class WindowsButton : public Button {
public:
    void paint() const override {
        std::cout << "This is a Windows Button." << std::endl;
    }
};

// MacOSButton.h
class MacOSButton : public Button {
public:
    void paint() const override {
        std::cout << "This is a MacOS Button." << std::endl;
    }
};

// WindowsCheckbox.h
class WindowsCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "This is a Windows Checkbox." << std::endl;
    }
};

// MacOSCheckbox.h
class MacOSCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "This is a MacOS Checkbox." << std::endl;
    }
};

// UIFactory.h
#include <memory>

class UIFactory {
public:
    virtual ~UIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// WindowsUIFactory.h
class WindowsUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WindowsCheckbox>();
    }
};

// MacOSUIFactory.h
class MacOSUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacOSButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacOSCheckbox>();
    }
};


void clientCode(const UIFactory& factory) {
    auto button = factory.createButton();
    auto checkbox = factory.createCheckbox();
    
    button->paint();
    checkbox->paint();
}

int main() {
    WindowsUIFactory windowsFactory;
    MacOSUIFactory macFactory;

    std::cout << "Client: Testing client code with the WindowsUIFactory:" << std::endl;
    clientCode(windowsFactory);

    std::cout << std::endl;

    std::cout << "Client: Testing the same client code with the MacOSUIFactory:" << std::endl;
    clientCode(macFactory);

    return 0;
}
