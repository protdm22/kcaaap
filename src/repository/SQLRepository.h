#pragma once
#include "IRepository.h"
#include "../../include/sqlite3.h"


class SQLRepository final : public IRepository {
private:
    sqlite3 *db{};

    void executeSQL(const std::string &sql) const;

public:
    explicit SQLRepository(const std::string &dbPath);

    ~SQLRepository() override;

    /**
     * Adds a dog to the sql repository.
     * @param dog the dog to be added
     */
    void add(const Dog &dog) override;

    /**
     * Updates a dog from the sql repository.
     * @param index the index of the dog to be updated
     * @param newDog the new dog
     */
    void update(int index, const Dog &newDog) override;

    /**
     * Removes a dog from the sql repository.
     * @param index the index of the dog to be removed
     */
    void remove(int index) override;

    /**
     * Gets all the dogs from the sql repository.
     * @return a pointer to the array of all the dogs
     */
    std::vector<Dog> getAllDogs() override;

    /**
     * Finds a dog in the sql repository.
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
     * Gets the size of the sql repository.
     * @return the size of the memory repository
     */
    [[nodiscard]] size_t size() const override;
};
