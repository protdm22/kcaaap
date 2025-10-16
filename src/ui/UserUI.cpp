#include <iostream>
#include "UserUI.h"

void printMenu() {
    std::cout << "--- Keep calm and adopt a pet [USER] ---\n";
    std::cout << "1. See dogs\n";
    std::cout << "2. See dogs filtered by breed and age\n";
    std::cout << "3. See adoption list\n";
    std::cout << "4. Save the adoption list to a file\n";
    std::cout << "5. Open the adoption list file\n";
    std::cout << "0. Exit\n>>> ";
}

void UserUI::showDogsOneByOne(const std::vector<Dog> &dogs) const {
    auto currentDog = dogs.begin();
    if (dogs.empty()) {
        std::cout << "No dogs available.\n";
        return;
    }
    int adoptedDogs = 0;
    while (true) {
        if (dogs.size() == adoptedDogs) {
            std::cout << "No more dogs available.\n";
            break;
        }
        if (currentDog == dogs.end()) {
            currentDog = dogs.begin();
        }
        if (!this->service.isAdopted(*currentDog)) {
            std::cout << "Name: " << UserService::capitalize(currentDog->getName()) << std::endl;
            std::cout << "Breed: " << UserService::capitalize(currentDog->getBreed()) << std::endl;
            std::cout << "Age: " << currentDog->getAge() << std::endl;
            openInBrowser(currentDog->getPhotoLink());
            std::string answer;
            std::cout << "Do you want to adopt " << UserService::capitalize(currentDog->getName()) <<
                    "? (yes/no)\n>>> ";
            std::cin >> answer;
            if (answer == "0" || answer == "exit" || answer == "q" || answer == "stop")
                break;
            if (answer == "yes") {
                this->service.addToAdoptionList(*currentDog);
                adoptedDogs++;
            }
        }
        ++currentDog;
    }
}

void UserUI::runUI() const {
    while (true) {
        printMenu();
        std::string option;
        std::cin >> option;
        if (option == "0")
            break;
        if (option == "1") {
            std::vector<Dog> allDogs = service.getAllDogs();
            showDogsOneByOne(allDogs);
            this->service.adoptDogs();
        } else if (option == "2") {
            std::string breed;
            int age;
            std::cout << "Enter breed: ";
            std::cin.ignore();
            std::getline(std::cin, breed);
            std::cout << "Enter age: ";
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
            std::vector<Dog> filteredDogs = service.getFilteredDogs(UserService::capitalize(breed), age);
            showDogsOneByOne(filteredDogs);
            this->service.adoptDogs();
        } else if (option == "3") {
            std::vector<Dog> adoptionList = service.getAdoptionList();
            if (adoptionList.empty()) {
                std::cout << "Adoption list is empty!\n\n";
            } else {
                std::cout << "--- Adoption list ---\n";
                int index = 1;
                for (auto &dog: adoptionList) {
                    std::cout << "\n----- Dog " << index << " -----" << std::endl;
                    std::cout << "Name: " << UserService::capitalize(dog.getName()) << std::endl;
                    std::cout << "Breed: " << UserService::capitalize(dog.getBreed()) << std::endl;
                    std::cout << "Age: " << dog.getAge() << std::endl;
                    std::cout << "Photo: " << dog.getPhotoLink() << std::endl;
                    index++;
                }
            }
        } else if (option == "4") {
            this->service.saveAdoptionListToFile();
            std::cout << "File saved" << std::endl;
        } else if (option == "5") {
            this->service.openAdoptionListFile();
        } else {
            std::cout << "Invalid option!\n\n";
        }
    }
}
