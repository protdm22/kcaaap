#include "AdoptionList.h"


void AdoptionList::add(const Dog &dog) {
    this->adoptedDogs.push_back(dog);
}

bool AdoptionList::isAdopted(const Dog &dog) const {
    return std::find(adoptedDogs.begin(), adoptedDogs.end(), dog) != adoptedDogs.end();
}
