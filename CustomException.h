#pragma once

class CustomException : public exception {
public:
    explicit CustomException(const string& message) : msg_(message) {}
    const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    string msg_;
};