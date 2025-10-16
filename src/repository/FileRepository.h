#pragma once
#include "IRepository.h"
#include <fstream>


class FileRepository final : public IRepository {
private:
    std::vector<Dog> dogs;
    std::string fileName;

    void loadFromFile();

    void saveToFile();

public:
    explicit FileRepository(const std::string &fileName) {
        this->fileName = fileName;
        this->loadFromFile();
    }

    ~FileRepository() override = default;

    /**
     * Adds a dog to the file repository.
     * @param dog the dog to be added
     */
    void add(const Dog &dog) override;

    /**
     * Updates a dog from the file repository.
     * @param index the index of the dog to be updated
     * @param newDog the new dog
     */
    void update(int index, const Dog &newDog) override;

    /**
     * Removes a dog from the file repository.
     * @param index the index of the dog to be removed
     */
    void remove(int index) override;

    /**
     * Gets all the dogs from the file repository.
     * @return a pointer to the array of all the dogs
     */
    std::vector<Dog> getAllDogs() override;

    /**
     * Finds a dog in the file repository.
     * @param dogToFind dog the dog to be found
     * @return the index of the dog if found, -1 otherwise
     */
    int find(const Dog &dogToFind) override;

    /**
     * Gets the dog at the given index.
     * @param index the index of the dog
     * @return the dog at the given index
     */
    Dog findByID(int index) override;

    /**
     * Gets the size of the file repository.
     * @return the size of the memory repository
     */
    [[nodiscard]] size_t size() const override;
};
