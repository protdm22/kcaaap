#pragma once
#include <vector>
#include "../domain/Dog.h"

class IRepository {
public:
    IRepository() = default;

    virtual ~IRepository() = default;

    /**
     * Adds a dog to the repository.
     * @param dog the dog to be added
     */
    virtual void add(const Dog &dog) = 0;

    /**
     * Updates a dog from the repository.
     * @param index the index of the dog to be updated
     * @param newDog the new dog
     */
    virtual void update(int index, const Dog &newDog) = 0;

    /**
     * Removes a dog from the repository.
     * @param index the index of the dog to be removed
     */
    virtual void remove(int index) = 0;

    /**
     * Gets all the dogs from the repository.
     * @return a pointer to the array of all the dogs
     */
    virtual std::vector<Dog> getAllDogs() = 0;

    /**
     * Finds a dog in the repository.
     * @param dogToFind dog the dog to be found
     * @return the index of the dog if found, -1 otherwise
     */
    virtual int find(const Dog &dogToFind) = 0;

    /**
     * Gets the dog at the given index.
     * @param index the index of the dog
     * @return the dog at the given index
     */
    virtual Dog findByID(int index) = 0;

    /**
        * Gets the size of the repository.
        * @return the size of the memory repository
        */
    [[nodiscard]] virtual size_t size() const = 0;
};
