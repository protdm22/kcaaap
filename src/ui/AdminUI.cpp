#include <iostream>

#include "AdminUI.h"

constexpr int EXIT = 0;
constexpr int SHOW_ALL_DOGS = 1;
constexpr int ADD_DOG = 2;
constexpr int UPDATE_DOG = 3;
constexpr int REMOVE_DOG = 4;

void printMainMenu() {
    std::cout << "--- Keep calm and adopt a pet [ADMIN] ---\n";
    std::cout << "1. See all dogs\n";
    std::cout << "2. Add a new dog\n";
    std::cout << "3. Update a dog's information\n";
    std::cout << "4. Remove dog from database\n";
    std::cout << "0. Exit\n>>> ";
}

void AdminUI::printDog(const Dog &dog) {
    std::cout << "Name: " << AdminService::capitalize(dog.getName()) << std::endl;
    std::cout << "Breed: " << AdminService::capitalize(dog.getBreed()) << std::endl;
    std::cout << "Age: " << dog.getAge() << std::endl;
    std::cout << "Photo: " << dog.getPhotoLink() << std::endl << std::endl;
}

void AdminUI::printAllDogs() const {
    const std::vector<Dog> allDogs = this->service.getAllDogs();
    int index = 1;
    for (const auto &dog: allDogs) {
        std::cout << "----- Dog " << index << " -----" << std::endl;
        printDog(dog);
        index++;
    }
    if (allDogs.empty())
        std::cout << "There are no dogs in the database!\n\n";
}

void AdminUI::addDog() const {
    std::string name, breed, photoLink;
    int age;

    std::cout << "---Add new dog---\nName: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Breed: ";
    std::getline(std::cin, breed);

    std::cout << "Age: ";
    try {
        std::cin >> age;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            throw std::runtime_error("Invalid input. Age must be an integer!");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl << std::endl;
        return;
    }

    std::cout << "Photo link: ";
    std::cin.ignore();
    std::getline(std::cin, photoLink);

    try {
        this->service.addDog(name, breed, age, photoLink);
        std::cout << "Dog added successfully\n\n";
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl << std::endl;
    }
}

void AdminUI::updateDog() const {
    std::string name, breed;
    int age;

    std::cout << "---Update dog---\nEnter the data for the dog you want to update:\nName: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Breed: ";
    std::getline(std::cin, breed);

    std::cout << "Age: ";
    try {
        std::cin >> age;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            throw std::runtime_error("Invalid input. Age must be an integer!");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl << std::endl;
        return;
    }

    try {
        const int index = this->service.findDog(name, breed, age);
        std::string newName, newBreed, newPhotoLink, newAge;

        std::cout << "Enter the new data for the dog (leave empty for no change):\nName: ";
        std::cin.ignore();
        std::getline(std::cin, newName);

        std::cout << "Breed: ";
        std::getline(std::cin, newBreed);

        std::cout << "Age: ";
        std::getline(std::cin, newAge);

        std::cout << "Photo link: ";
        std::getline(std::cin, newPhotoLink);
        this->service.updateDog(index, newName, newBreed, newAge, newPhotoLink);
        std::cout << "Dog updated successfully\n\n";
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl << std::endl;
    }
}

void AdminUI::removeDog() const {
    std::string name, breed;
    int age;

    std::cout << "---Delete dog---\nEnter the data for the dog you want to delete:\nName: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Breed: ";
    std::getline(std::cin, breed);

    std::cout << "Age: ";
    try {
        std::cin >> age;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            throw std::runtime_error("Invalid input. Age must be an integer!");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl << std::endl;
        return;
    }

    try {
        this->service.removeDog(name, breed, age);
        std::cout << "Dog removed successfully\n\n";
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl << std::endl;
    }
}

void AdminUI::runUI() const {
    int option;
    while (true) {
        printMainMenu();
        std::cin >> option;
        if (option == EXIT)
            break;
        if (option == SHOW_ALL_DOGS) {
            printAllDogs();
        } else if (option == ADD_DOG) {
            addDog();
        } else if (option == UPDATE_DOG) {
            updateDog();
        } else if (option == REMOVE_DOG) {
            removeDog();
        }
    }
}
