#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <string>

class Logger {
public:
    // Method to get the single instance of the Logger class
    static Logger& getInstance() { 
        static Logger instance;
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copying
    Logger(const Logger&) = delete;   //String str3 = str1
    Logger& operator=(const Logger&) = delete;   // strg3 = strng4 



    // Method to log info messages
    void logInfo(const std::string& message) {
        log("INFO", message);
    }

    // Method to log warning messages
    void logWarning(const std::string& message) {
        log("WARNING", message);
    }

    // Method to log error messages
    void logError(const std::string& message) {
        log("ERROR", message);
    }

private:
    // Private constructor to prevent direct instantiation
    Logger()
        : logFile_("log.txt", std::ios::app) {
        if (!logFile_) {
            throw std::runtime_error("Unable to open log file.");
        }
    }

    // Private method to log messages with a specified label
    void log(const std::string& label, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        logFile_ << label << ": " << message << std::endl;
    }

    std::ofstream logFile_;
    std::mutex mutex_;
};


int main() {

    // Access the Singleton logger instance and log various messages
    Logger& logger = Logger::getInstance();

    logger.logInfo("Application started");
    logger.logWarning("Low disk space warning");
    logger.logError("Read-only file system error");

    // Simulate further logging in another part of the application
    Logger& anotherLoggerReference = Logger::getInstance();
    anotherLoggerReference.logInfo("Another operation completed");

    // Verify that both logger instances are the same
    if (&logger == &anotherLoggerReference) {
        std::cout << "Both instances are the same." << std::endl;
    } else {
        std::cout << "Instances are different." << std::endl;
    }

    return 0;
}
