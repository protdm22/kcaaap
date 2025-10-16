#include "AdminService.h"

#include <algorithm>
#include <stdexcept>

#include "../exceptions/ServiceException.h"
#include "../utils/GeneratorUtils.h"

void AdminService::addDog(const std::string &name, const std::string &breed, const int age,
                          const std::string &photoLink) {
    const auto newDog = Dog(capitalize(name), capitalize(breed), age, photoLink);
    DogValidator::validate(newDog);
    if (this->repository->find(newDog) != -1)
        throw ServiceException("Dog already exists");
    this->repository->add(newDog);
    this->undoStack.push(std::move(std::make_unique<ActionAdd>(newDog, *this->repository)));
}

void AdminService::updateDog(const int index, const std::string &name, const std::string &breed, const std::string &age,
                             const std::string &photoLink) {
    if (index < 0)
        throw ServiceException("Dog does not exist");

    const Dog oldDog = this->repository->findByID(index);
    const std::string newName = name.empty() ? oldDog.getName() : name;
    const std::string newBreed = breed.empty() ? oldDog.getBreed() : breed;

    int newAge;
    if (age.empty()) {
        newAge = oldDog.getAge();
    } else {
        try {
            newAge = stringToInt(age);
        } catch (const std::exception &) {
            throw ServiceException("Invalid age");
        }
    }

    const std::string newPhotoLink = photoLink.empty() ? oldDog.getPhotoLink() : photoLink;

    const auto newDog = Dog(capitalize(newName), capitalize(newBreed), newAge, newPhotoLink);
    DogValidator::validate(newDog);
    this->repository->update(index, newDog);
    this->undoStack.push(std::move(std::make_unique<ActionUpdate>(oldDog, newDog, *this->repository)));
}

void AdminService::removeDog(const std::string &name, const std::string &breed, const int age) {
    const Dog dog(capitalize(name), capitalize(breed), age, "");
    const int index = this->repository->find(dog);
    if (index == -1)
        throw ServiceException("Dog does not exist");
    const auto deletedDog = this->repository->findByID(index);
    this->repository->remove(index);
    this->undoStack.push(std::move(std::make_unique<ActionRemove>(deletedDog, *this->repository)));
}

int AdminService::findDog(const std::string &name, const std::string &breed, const int age) const {
    const Dog dog(capitalize(name), capitalize(breed), age, "");
    const int index = this->repository->find(dog);
    return index;
}

std::vector<Dog> AdminService::getAllDogs() const {
    return this->repository->getAllDogs();
}

size_t AdminService::repositorySize() const {
    return this->repository->size();
}

std::string AdminService::capitalize(const std::string &string) {
    std::string result = string;
    bool capitalizeNext = true;

    std::transform(result.begin(), result.end(), result.begin(), [&capitalizeNext](char character) {
        if (std::isspace(character)) {
            capitalizeNext = true;
            return character;
        } else if (capitalizeNext) {
            capitalizeNext = false;
            return static_cast<char>(std::toupper(character));
        } else {
            return static_cast<char>(std::tolower(character));
        }
    });

    return result;
}

int AdminService::stringToInt(const std::string &string) {
    try {
        return std::stoi(string);
    } catch (const std::exception &) {
        throw ServiceException("Invalid age");
    }
}

void AdminService::undo() {
    if (this->undoStack.empty()) {
        throw ServiceException("No more undoes available");
    }
    std::unique_ptr<Action> action = std::move(this->undoStack.top());
    this->undoStack.pop();
    action->executeUndo();
    this->redoStack.push(std::move(action));
}

void AdminService::redo() {
    if (this->redoStack.empty()) {
        throw ServiceException("No more redoes available");
    }
    std::unique_ptr<Action> action = std::move(this->redoStack.top());
    this->redoStack.pop();
    action->executeRedo();
    this->undoStack.push(std::move(action));
}
