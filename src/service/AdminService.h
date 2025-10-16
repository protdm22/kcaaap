#pragma once
#include "../repository/IRepository.h"
#include <memory>
#include <stack>

#include "UndoRedo.h"

class AdminService {
private:
    IRepository *repository;

    std::stack<std::unique_ptr<Action> > undoStack;
    std::stack<std::unique_ptr<Action> > redoStack;

    static int stringToInt(const std::string &string);

public:
    /// Creates a new service.
    explicit AdminService(IRepository *repository): repository(repository) {
    };

    /**
     * Adds a new dog to the repository.
     * @param name The name of the dog.
     * @param breed The breed of the dog.
     * @param age The age of the dog.
     * @param photoLink The link to the photo of the dog.
     */
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photoLink);

    /**
     * Updates a dog from the repository.
     * @param index The index of the dog to update.
     * @param name The new name of the dog.
     * @param breed The new breed of the dog.
     * @param age The new age of the dog.
     * @param photoLink The new link to the photo of the dog.
     */
    void updateDog(int index, const std::string &name, const std::string &breed, const std::string &age,
                   const std::string &photoLink);

    /**
     * Removes a dog from the repository.
     * @param name The name of the dog.
     * @param breed The breed of the dog.
     * @param age The age of the dog.
     */
    void removeDog(const std::string &name, const std::string &breed, int age);

    /**
     * Finds a dog in the repository.
     * @param name The name of the dog.
     * @param breed The breed of the dog.
     * @param age The age of the dog.
     * @return The index of the dog if it was found, -1 otherwise.
     */
    [[nodiscard]] int findDog(const std::string &name, const std::string &breed, int age) const;

    /**
     * Returns all the dogs from the repository.
     * @return All the dogs from the repository.
     */
    [[nodiscard]] std::vector<Dog> getAllDogs() const;

    /**
     * Returns the size of the repository.
     * @return The size of the repository.
     */
    [[nodiscard]] size_t repositorySize() const;

    /**
     * Capitalizes the first letter of every word in a string.
     * @param string The string to capitalize.
     * @return The string with the first letter of every word capitalized.
     */
    static std::string capitalize(const std::string &string);

    void undo();

    void redo();
};
