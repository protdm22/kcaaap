#pragma once

#include "../service/AdminService.h"

class AdminUI {
private:
    AdminService &service;

    /// Helper function to display a single dog
    static void printDog(const Dog &dog);

    /// Helper function to display all dogs
    void printAllDogs() const;

    /// Helper function to add a dog
    void addDog() const;

    /// Helper function to update a dog
    void updateDog() const;

    /// Helper function to remove a dog
    void removeDog() const;

public:
    /**
     * Constructor for AdminUI
     * @param service The admin service to use
     */
    explicit AdminUI(AdminService &service) : service(service) {
    }

    /// Runs the admin UI
    void runUI() const;
};
