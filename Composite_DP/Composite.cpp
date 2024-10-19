#include <string>
#include <iostream>
#include <vector>
#include <memory>

// FileSystemComponent.h
class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    
    virtual void add(std::shared_ptr<FileSystemComponent> component) {
        throw std::runtime_error("Cannot add to a leaf");
    }
    
    virtual void remove(std::shared_ptr<FileSystemComponent> component) {
        throw std::runtime_error("Cannot remove from a leaf");
    }
    
    virtual void display(int depth) const = 0;
};

// File.h
class File : public FileSystemComponent {
public:
    explicit File(const std::string& name) : name_(name) {}
    
    void display(int depth) const override {
        std::string indent(depth, '-');
        std::cout << indent << name_ << std::endl;
    }
    
private:
    std::string name_;
};


// Directory.h
class Directory : public FileSystemComponent {
public:
    explicit Directory(const std::string& name) : name_(name) {}
    
    void add(std::shared_ptr<FileSystemComponent> component) override {
        children_.emplace_back(component);
    }
    
    void remove(std::shared_ptr<FileSystemComponent> component) override {
        children_.erase(std::remove(children_.begin(), children_.end(), component), children_.end());
    }
    
    void display(int depth) const override {
        std::string indent(depth, '-');
        std::cout << indent << name_ << std::endl;
        for (const auto& child : children_) {
            child->display(depth + 2);
        }
    }
    
private:
    std::string name_;
    std::vector<std::shared_ptr<FileSystemComponent>> children_;
};

int main() {
    // Create files
    std::shared_ptr<FileSystemComponent> file1 = std::make_shared<File>("File1.txt");
    std::shared_ptr<FileSystemComponent> file2 = std::make_shared<File>("File2.txt");
    std::shared_ptr<FileSystemComponent> file3 = std::make_shared<File>("File3.txt");

    // Create directories
    std::shared_ptr<FileSystemComponent> rootDir = std::make_shared<Directory>("root");
    std::shared_ptr<FileSystemComponent> subdir1 = std::make_shared<Directory>("subdir1");
    std::shared_ptr<FileSystemComponent> subdir2 = std::make_shared<Directory>("subdir2");

    // Build hierarchy
    rootDir->add(file1);
    rootDir->add(subdir1);
    subdir1->add(file2);
    subdir1->add(subdir2);
    subdir2->add(file3);

    // Display the file system hierarchy
    rootDir->display(0);

    return 0;
}

rootdir

vector {{file1} {}}