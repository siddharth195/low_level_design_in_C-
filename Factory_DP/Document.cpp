#include <iostream>

class Document {
public:
    virtual ~Document() = default;
    virtual void printType() const = 0;  // Abstract method
};

class PDFDocument : public Document {
public:
    void printType() const override {
        std::cout << "This is a PDF document." << std::endl;
    }
};

class WordDocument : public Document {
public:
    void printType() const override {
        std::cout << "This is a Word document." << std::endl;
    }
};

class ExcelDocument : public Document {
public:
    void printType() const override {
        std::cout << "This is an Excel document." << std::endl;
    }
};



class DocumentFactory {
public:
    virtual ~DocumentFactory() = default;
    virtual std::unique_ptr<Document> createDocument() const = 0;  // Factory method
};

class PDFDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument() const override {
        return std::make_unique<PDFDocument>();
    }
};

class WordDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument() const override {
        return std::make_unique<WordDocument>();
    }
};

class ExcelDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument() const override {
        return std::make_unique<ExcelDocument>();
    }
};

int main() {
    // Create factories
    PDFDocumentFactory pdfFactory;
    WordDocumentFactory wordFactory;
    ExcelDocumentFactory excelFactory;

    // Create documents using factories
    std::unique_ptr<Document> pdf = pdfFactory.createDocument();
    std::unique_ptr<Document> word = wordFactory.createDocument();
    std::unique_ptr<Document> excel = excelFactory.createDocument();

    // Use the documents
    pdf->printType();
    word->printType();
    excel->printType();

    return 0;
}



