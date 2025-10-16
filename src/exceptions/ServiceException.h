#pragma once
#include "ApplicationException.h"


class ServiceException final : public ApplicationException {
public:
    explicit ServiceException(const std::string &_message): ApplicationException(_message) {
    };
};
