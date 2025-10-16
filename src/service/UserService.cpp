#include "UserService.h"
#include "../utils/GeneratorUtils.h"

std::vector<Dog> UserService::getAllDogs() const {
    return this->repository->getAllDogs();
}

size_t UserService::repositorySize() const {
    return this->repository->size();
}

std::string UserService::capitalize(const std::string &string) {
    std::string result = string;
    bool capitalizeNext = true;

    std::ranges::transform(result, result.begin(), [&capitalizeNext](char character) {
        if (std::isspace(character)) {
            capitalizeNext = true;
            return character;
        }
        if (capitalizeNext) {
            capitalizeNext = false;
            return static_cast<char>(std::toupper(character));
        }
        return static_cast<char>(std::tolower(character));
    });

    return result;
}

std::vector<Dog> UserService::getFilteredDogs(const std::string &breed, const int age) const {
    const std::vector<Dog> allDogs = this->repository->getAllDogs();
    std::vector<Dog> filteredDogs;
    std::ranges::copy_if(allDogs, std::back_inserter(filteredDogs), [&](const Dog &dog) {
        if (breed.empty())
            return dog.getAge() < age;
        return capitalize(dog.getBreed()) == capitalize(breed) && dog.getAge() < age;
    });
    return filteredDogs;
}

void UserService::addToAdoptionList(const Dog &dog) const {
    this->adoptionList.add(dog);
}

void UserService::adoptDogs() const {
    for (const auto &adoptedDog: adoptionList.getAdoptionList())
        this->repository->remove(this->repository->find(adoptedDog));
}

void UserService::saveAdoptionListToFile() const {
    this->adoptionList.writeToFile();
}

void UserService::openAdoptionListFile() const {
    this->adoptionList.displayAdoptionList();
}
