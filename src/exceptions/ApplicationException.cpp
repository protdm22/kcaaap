#include "ApplicationException.h"

ApplicationException::ApplicationException(const std::string &_message) {
    this->message = _message;
}

const char *ApplicationException::what() const noexcept {
    return this->message.c_str();
}
