#include "FileRepository.h"

#include "../exceptions/RepositoryException.h"

void FileRepository::loadFromFile() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw RepositoryException("Could not open file: " + fileName);
    }
    Dog dog;
    while (file >> dog) {
        this->dogs.push_back(dog);
    }
    file.close();
}

void FileRepository::saveToFile() {
    std::ofstream file(fileName);
    for (const auto &dog: getAllDogs()) {
        file << dog << "\n";
    }
    file.close();
}

void FileRepository::add(const Dog &dog) {
    this->dogs.push_back(dog);
    saveToFile();
}

void FileRepository::update(const int index, const Dog &newDog) {
    this->dogs.erase(this->dogs.begin() + index);
    this->dogs.push_back(newDog);
    saveToFile();
}

void FileRepository::remove(const int index) {
    if (index < 0 || index >= this->dogs.size())
        return;
    this->dogs.erase(this->dogs.begin() + index);
    saveToFile();
}

std::vector<Dog> FileRepository::getAllDogs() {
    return this->dogs;
}

int FileRepository::find(const Dog &dogToFind) {
    int index = 0;
    for (const auto &dog: this->dogs) {
        if (dogToFind == dog)
            return index;
        index++;
    }
    return -1;
}

Dog FileRepository::findByID(const int index) {
    return this->dogs[index];
}


size_t FileRepository::size() const {
    return this->dogs.size();
}
