#include "MemoryRepository.h"


void MemoryRepository::add(const Dog &dog) {
    this->dogs.push_back(dog);
}

void MemoryRepository::update(const int index, const Dog &newDog) {
    this->dogs.erase(this->dogs.begin() + index);
    this->dogs.push_back(newDog);
}

void MemoryRepository::remove(const int index) {
    if (index < 0 || index >= this->dogs.size())
        return;
    this->dogs.erase(this->dogs.begin() + index);
}

std::vector<Dog> MemoryRepository::getAllDogs() {
    return this->dogs;
}

int MemoryRepository::find(const Dog &dogToFind) {
    int index = 0;
    for (const auto &dog: this->dogs) {
        if (dogToFind == dog)
            return index;
        index++;
    }
    return -1;
}

Dog MemoryRepository::findByID(const int index) {
    return this->dogs[index];
}


size_t MemoryRepository::size() const {
    return this->dogs.size();
}
