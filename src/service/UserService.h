#pragma once

#include <algorithm>
#include <qobject.h>
#include <string>

#include "FileAdoptionList.h"
#include "../repository/IRepository.h"

class UserService {
private:
    IRepository *repository;
    FileAdoptionList &adoptionList;

public:
    /// Constructor for UserService
    explicit UserService(IRepository *repository, FileAdoptionList &adoptionList) : repository(repository),
        adoptionList(adoptionList) {
    };

    /// Returns the list of all dogs
    [[nodiscard]] std::vector<Dog> getAllDogs() const;

    /// Returns the number of dogs in the repository
    [[nodiscard]] size_t repositorySize() const;

    /// Capitalizes the first letter of every word in a string
    static std::string capitalize(const std::string &string);

    /**
     * Filters the dogs in the repository based on breed and age
     * @param breed The breed to filter by
     * @param age The age to filter by
     * @return A pointer to the filtered dog list
     */
    [[nodiscard]] std::vector<Dog> getFilteredDogs(const std::string &breed, int age) const;

    /**
     * Adds a dog to the adoption list
     * @param dog The dog to be added
     */
    void addToAdoptionList(const Dog &dog) const;

    /**
     * Returns all the dogs from the repository.
     * @return All the dogs from the repository.
     */
    [[nodiscard]] std::vector<Dog> getAdoptionList() const {
        return this->adoptionList.getAdoptionList();
    };

    /**
     * Removes the dog from the adoption list from the repository
     */
    void adoptDogs() const;

    /**
     * Checks if a dog is already adopted
     * @param dog The dog to check
     * @return True if the dog is adopted, false otherwise
     */
    [[nodiscard]] bool isAdopted(const Dog &dog) const {
        return adoptionList.isAdopted(dog);
    };

    /**
     * Saves the adoption list to a file
     */
    void saveAdoptionListToFile() const;

    /**
     * Opens the adoption list file
     */
    void openAdoptionListFile() const;
};
