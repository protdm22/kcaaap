#pragma once
#include <string>


class ApplicationException : public std::exception {
private:
    std::string message;

public:
    explicit ApplicationException(const std::string &_message);

    const char *what() const noexcept override;
};
