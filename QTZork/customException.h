#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <exception>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;

public:
    //prevents implicit conversions. Compiler wont automatically convert types without explicit casting or initialization.
    explicit CustomException(const std::string& msg) : message(msg) {}

    //returns a const char* pointer to the exception message.
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // CUSTOMEXCEPTION_H
