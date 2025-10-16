#include "Dog.h"
#include <regex>
#include "../exceptions/DomainException.h"

Dog::Dog() {
    this->name = "";
    this->breed = "";
    this->age = 0;
    this->photoLink = "";
}

Dog::Dog(const std::string &name, const std::string &breed, const int age, const std::string &photoLink) {
    this->name = name;
    this->breed = breed;
    this->age = age;
    this->photoLink = photoLink;
}

void DogValidator::validate(const Dog &dog) {
    std::string errors;
    if (dog.getName().empty()) {
        errors += "Dog name cannot be empty!\n";
    }
    if (dog.getBreed().empty()) {
        errors += "Dog breed cannot be empty!\n";
    }
    if (dog.getAge() < 0) {
        errors += "Age must be a positive number!\n";
    }
    if (!isValidURL(dog.getPhotoLink())) {
        errors += "Invalid photo link!\n";
    }
    if (!errors.empty())
        throw DomainException(errors);
}

bool DogValidator::isValidURL(const std::string &url) {
    const std::regex urlRegex(R"(^(https?|ftp):\/\/[^\s/$.?#].[^\s]*$)");
    return std::regex_match(url, urlRegex);
}
