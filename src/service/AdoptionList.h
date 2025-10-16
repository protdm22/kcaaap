#pragma once
#include <vector>
#include <algorithm>

#include "../domain/Dog.h"


class AdoptionList {
protected:
    std::vector<Dog> adoptedDogs;

public:
    /**
     * Adds a dog to the adoption list
     * @param dog The dog to be added
     */
    void add(const Dog &dog);

    /**
     * Returns the adoption list
     * @return the adoption list
     */
    [[nodiscard]] std::vector<Dog> getAdoptionList() const {
        return this->adoptedDogs;
    };

    /**
     * Checks if a dog is already adopted
     * @param dog The dog to check
     * @return True if the dog is adopted, false otherwise
     */
    [[nodiscard]] bool isAdopted(const Dog &dog) const;
};
