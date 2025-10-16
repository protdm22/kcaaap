#pragma once
#include "ApplicationException.h"


class RepositoryException final : public ApplicationException {
public:
    explicit RepositoryException(const std::string &_message) : ApplicationException(_message) {
    };
};
