// Iterator.h
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};


// Aggregate.h
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
};

#include <vector>
#include <string>
#include <memory>
#include <iostream>

// BookCollection.h
class BookCollection;

// BookCollectionIterator.h
class BookCollectionIterator : public Iterator<std::string> {
public:
    BookCollectionIterator(const BookCollection& collection);

    bool hasNext() const override;
    std::string next() override;

private:
    const BookCollection& collection_;
    size_t currentIndex_;
};

// BookCollection.h
class BookCollection : public Aggregate<std::string> {
public:
    void addBook(const std::string& book) {
        books_.push_back(book);
    }

    std::unique_ptr<Iterator<std::string>> createIterator() const override {
        return std::make_unique<BookCollectionIterator>(*this);
    }

    size_t getSize() const {
        return books_.size();
    }

    std::string getBookAt(size_t index) const {
        if (index < books_.size()) {
            return books_[index];
        }
        return "";
    }

private:
    std::vector<std::string> books_;
};

// BookCollectionIterator.cpp
BookCollectionIterator::BookCollectionIterator(const BookCollection& collection)
    : collection_(collection), currentIndex_(0) {}

bool BookCollectionIterator::hasNext() const {
    return currentIndex_ < collection_.getSize();
}

std::string BookCollectionIterator::next() {
    if (!hasNext()) {
        throw std::out_of_range("No more elements.");
    }
    return collection_.getBookAt(currentIndex_++);
}

#include "BookCollection.h"
#include "BookCollectionIterator.h"

int main() {
    // Create a book collection and add books to it
    BookCollection myBooks;
    myBooks.addBook("1984");
    myBooks.addBook("To Kill a Mockingbird");
    myBooks.addBook("The Great Gatsby");

    // Create an iterator for the book collection
    std::unique_ptr<Iterator<std::string>> it = myBooks.createIterator();

    // Traverse the book collection using the iterator
    while (it->hasNext()) {
        std::string book = it->next();
        std::cout << "Book: " << book << std::endl;
    }

    return 0;
}
