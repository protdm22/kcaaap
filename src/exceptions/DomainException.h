#pragma once
#include "ApplicationException.h"


class DomainException final : public ApplicationException {
public:
    explicit DomainException(const std::string& _message) : ApplicationException(_message) {
    };
};
