#include "Tests.h"

#include <cassert>
#include <iostream>

#include "../src/utils/GeneratorUtils.h"
#include "../src/repository/FileRepository.h"
#include "../src/repository/SQLRepository.h"
#include "../src/domain/Dog.h"
#include "../src/exceptions/DomainException.h"
#include "../src/exceptions/RepositoryException.h"
#include "../src/exceptions/ServiceException.h"
#include "../src/repository/MemoryRepository.h"
#include "../src/service/AdminService.h"
#include "../src/service/UserService.h"
#include "../utils/Comparator.h"


void Tests::testMemoryRepository() {
    MemoryRepository repository;
    assert(repository.size() == 0);

    // Test add
    repository.add(Dog("Rex", "Husky", 3, "https://www.google.com"));
    assert(repository.size() == 1);
    repository.add(Dog("Max", "Golden Retriever", 2, "https://www.google.com"));
    assert(repository.size() == 2);

    // Test find
    assert(repository.find(Dog("Rex", "Husky", 3, "https://www.google.com")) == 0);
    assert(repository.find(Dog("Max", "Golden Retriever", 2, "https://www.google.com")) == 1);
    assert(repository.find(Dog("Rex", "Golden Retriever", 3, "https://www.google.com")) == -1);

    // Test findByID
    assert(repository.findByID(0) == Dog("Rex", "Husky", 3, "https://www.google.com"));

    // Test remove
    repository.remove(0);
    assert(repository.size() == 1);
    assert(repository.find(Dog("Rex", "Husky", 3, "https://www.google.com")) == -1);
    assert(repository.find(Dog("Max", "Golden Retriever", 2, "https://www.google.com")) == 0);

    repository.remove(-1);

    // Test getAll
    const auto allDogs = repository.getAllDogs();
    assert(allDogs[0] == Dog("Max", "Golden Retriever", 2, "https://www.google.com"));

    // Test update
    repository.update(0, Dog("Max", "Golden Retriever", 3, "https://www.google.com"));
    assert(repository.find(Dog("Max", "Golden Retriever", 3, "https://www.google.com")) == 0);

    for (const auto &entry: repository.getAllDogs())
        repository.remove(repository.find(entry));
}

void Tests::testFileRepository() {
    FileRepository repository("test.txt");
    assert(repository.size() == 0);

    // Test add
    repository.add(Dog("Rex", "Husky", 3, "https://www.google.com"));
    assert(repository.size() == 1);
    repository.add(Dog("Max", "Golden Retriever", 2, "https://www.google.com"));
    assert(repository.size() == 2);

    // Test find
    assert(repository.find(Dog("Rex", "Husky", 3, "https://www.google.com")) == 0);
    assert(repository.find(Dog("Max", "Golden Retriever", 2, "https://www.google.com")) == 1);
    assert(repository.find(Dog("Rex", "Golden Retriever", 3, "https://www.google.com")) == -1);

    // Test findByID
    assert(repository.findByID(0) == Dog("Rex", "Husky", 3, "https://www.google.com"));

    // Test remove
    repository.remove(0);
    assert(repository.size() == 1);
    assert(repository.find(Dog("Rex", "Husky", 3, "https://www.google.com")) == -1);
    assert(repository.find(Dog("Max", "Golden Retriever", 2, "https://www.google.com")) == 0);

    // Test getAll
    const auto allDogs = repository.getAllDogs();
    assert(allDogs[0] == Dog("Max", "Golden Retriever", 2, "https://www.google.com"));

    // Test update
    repository.update(0, Dog("Max", "Golden Retriever", 3, "https://www.google.com"));
    assert(repository.find(Dog("Max", "Golden Retriever", 3, "https://www.google.com")) == 0);

    for (auto &entry: repository.getAllDogs())
        repository.remove(repository.find(entry));

    const std::string filename = "non_existent_file.txt";
    std::remove(filename.c_str());

    bool exceptionThrown = false;
    try {
        FileRepository repo(filename);
    } catch (RepositoryException &e) {
        exceptionThrown = true;
        assert(std::string(e.what()).find("Could not open file") != std::string::npos);
    }
    assert(exceptionThrown);
}

void Tests::testSQLRepository() {
    SQLRepository repository("test.db");
    assert(repository.size() == 0);

    // Test add
    repository.add(Dog("Rex", "Husky", 3, "https://www.google.com"));
    assert(repository.size() == 1);
    repository.add(Dog("Max", "Golden Retriever", 2, "https://www.google.com"));
    assert(repository.size() == 2);

    // Test find
    int index = repository.find(Dog("Rex", "Husky", 3, "https://www.google.com"));

    // Test findByID
    assert(repository.findByID(index) == Dog("Rex", "Husky", 3, "https://www.google.com"));

    // Test remove
    repository.remove(index);
    assert(repository.size() == 1);
    assert(repository.find(Dog("Rex", "Husky", 3, "https://www.google.com")) == -1);

    // Test getAll
    const auto allDogs = repository.getAllDogs();
    assert(allDogs[0] == Dog("Max", "Golden Retriever", 2, "https://www.google.com"));

    index = repository.find(Dog("Max", "Golden Retriever", 2, "https://www.google.com"));
    // Test update
    repository.update(index, Dog("Max", "Golden Retriever", 3, "https://www.google.com"));
    assert(repository.find(Dog("Max", "Golden Retriever", 3, "https://www.google.com")) == index);
    for (const auto &entry: repository.getAllDogs())
        repository.remove(repository.find(entry));
}


void Tests::testAdminService() {
    MemoryRepository repository;
    AdminService service(&repository);
    assert(service.repositorySize() == 0);

    // Test add
    service.addDog("Rex", "Husky", 3, "https://www.google.com");
    assert(service.repositorySize() == 1);
    service.addDog("Max", "Golden Retriever", 2, "https://www.google.com");
    assert(service.repositorySize() == 2);

    try {
        service.addDog("Max", "Golden Retriever", 2, "https://www.google.com");
    } catch (ServiceException &) {
        assert(true);
    }

    // Test find
    assert(service.findDog("Rex", "Husky", 3) == 0);
    assert(service.findDog("Max", "Golden Retriever", 2) == 1);
    assert(service.findDog("Rex", "Golden Retriever", 3) == -1);

    // Test remove
    service.removeDog("Rex", "Husky", 3);
    assert(service.repositorySize() == 1);
    assert(service.findDog("Rex", "Husky", 3) == -1);
    assert(service.findDog("Max", "Golden Retriever", 2) == 0);
    try {
        service.removeDog("Rex", "Husky", 2);\
    } catch (ServiceException &) {
        assert(true);
    }

    // Test getAll
    const auto allDogs = service.getAllDogs();
    assert(allDogs[0] == Dog("Max", "Golden Retriever", 2, "https://www.google.com"));

    // Test update
    service.updateDog(0, "Max", "Golden Retriever", "3", "https://www.google.com");
    assert(service.findDog("Max", "Golden Retriever", 3) == 0);
    service.updateDog(0, "Rex", "Golden Retriever", "", "https://www.google.com");
    assert(service.findDog("Rex", "Golden Retriever", 3) == 0);
    try {
        service.updateDog(0, "Rex", "Golden Retriever", "aaa", "https://www.google.com");
    } catch (ServiceException &) {
        assert(true);
    }
    try {
        service.updateDog(-2, "Rex", "Golden Retriever", "aaa", "https://www.google.com");
    } catch (ServiceException &) {
        assert(true);
    }

    // Test capitalize
    assert(AdminService::capitalize("rex") == "Rex");
    assert(AdminService::capitalize("REX") == "Rex");
    assert(AdminService::capitalize("rEx") == "Rex");
    assert(AdminService::capitalize("rEX") == "Rex");
    assert(AdminService::capitalize("Rex") == "Rex");

    for (const auto &entry: repository.getAllDogs())
        repository.remove(repository.find(entry));
}

void Tests::testUserService() {
    MemoryRepository repository;

    FileAdoptionList *fileAdoptionList = new CSVAdoptionList{"test.csv"};
    const UserService service(&repository, *fileAdoptionList);
    assert(service.repositorySize() == 0);

    AdminService adminService(&repository);
    GeneratorUtils::initializeEntries(&adminService);

    // Test addToAdoptionList
    service.addToAdoptionList(service.getAllDogs()[0]);

    assert(
        service.getAdoptionList()[0] == Dog("Max", "Bulldog", 2,
            "https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/Bulldog_inglese.jpg/1200px-Bulldog_inglese.jpg"
        ));
    service.adoptDogs();
    assert(service.repositorySize() == 9);

    // Test getAllDogs
    const auto allDogs = service.getAllDogs();
    assert(
        allDogs[0] == Dog("Bella", "Poodle", 4,
            "https://www.dogster.com/wp-content/uploads/2023/08/red-toy-poodle-in-the-park_Mykhaylo_Kozelko_Shutterstock.jpg"
        ));

    // Test getFilteredDogs
    const auto filteredDogs = service.getFilteredDogs("Poodle", 5);
    assert(filteredDogs[0] == Dog("Bella", "Poodle", 4,
        "https://www.dogster.com/wp-content/uploads/2023/08/red-toy-poodle-in-the-park_Mykhaylo_Kozelko_Shutterstock.jpg"
    ));
    const auto filteredDogs2 = service.getFilteredDogs("", 2);
    assert(filteredDogs2[0] == Dog("Lola", "Pug", 1, "https://cdn.britannica.com/35/233235-050-8DED07E3/Pug-dog.jpg"));

    // Test getFilteredDogs with no results
    constexpr int noResultsSize = 0;
    const auto noResults = service.getFilteredDogs("Poodle", 1);
    assert(noResultsSize == 0);

    // Test getAdoptionList
    assert(service.isAdopted(Dog("Max", "Bulldog", 2,
            "https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/Bulldog_inglese.jpg/1200px-Bulldog_inglese.jpg"))
        ==
        true);
    const auto adoptionList = service.getAdoptionList();
    assert(adoptionList.size() == 1);
    assert(
        adoptionList[0] == Dog("Max", "Bulldog", 2,
            "https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/Bulldog_inglese.jpg/1200px-Bulldog_inglese.jpg"
        ));

    // Test capitalize
    assert(UserService::capitalize("rex") == "Rex");
    assert(UserService::capitalize("REX") == "Rex");
    assert(UserService::capitalize("rEx") == "Rex");
    assert(UserService::capitalize("rEX rex") == "Rex Rex");

    for (const auto &entry: repository.getAllDogs())
        repository.remove(repository.find(entry));

    // Test saveAdoptionListToFile
    service.saveAdoptionListToFile();
    std::ifstream file("test.csv");
    assert(file.is_open());

    delete fileAdoptionList;
}

void Tests::testDomain() {
    const Dog dog1("Rex", "Husky", 3, "https://www.google.com");
    assert(dog1.getName() == "Rex");
    assert(dog1.getBreed() == "Husky");
    assert(dog1.getAge() == 3);
    assert(dog1.getPhotoLink() == "https://www.google.com");

    DogValidator::validate(dog1);
    assert(true);

    try {
        const Dog dog2("", "", -1, "www.google.com");
        DogValidator::validate(dog2);
    } catch (DomainException &) {
        assert(true);
    }
}

void Tests::testAdoptionList() {
    FileAdoptionList *fileAdoptionList = new CSVAdoptionList{"test.csv"};
    fileAdoptionList->add(Dog("Rex", "Husky", 3, "https://www.google.com"));
    fileAdoptionList->add(Dog("Max", "Golden Retriever", 2, "https://www.google.com"));
    fileAdoptionList->writeToFile();

    delete fileAdoptionList;

    fileAdoptionList = new HTMLAdoptionList{"test.html"};
    fileAdoptionList->add(Dog("Rex", "Husky", 3, "https://www.google.com"));
    fileAdoptionList->add(Dog("Max", "Golden Retriever", 2, "https://www.google.com"));
    fileAdoptionList->writeToFile();

    delete fileAdoptionList;
}

void Tests::testComparator() {
    std::vector<Dog> dogs;
    dogs.push_back(Dog("Rex", "Husky", 3, "https://www.google.com"));
    dogs.push_back(Dog("Max", "Husky", 2, "https://www.google.com"));
    dogs.push_back(Dog("Arthur", "Husky", 5, "https://www.google.com"));

    // Sort by name (ascending)
    ComparatorAscendingByName nameComp;
    customSort(dogs, &nameComp);

    assert(dogs[0].getName() == "Arthur");
    assert(dogs[1].getName() == "Max");
    assert(dogs[2].getName() == "Rex");

    // Sort by age (ascending)
    ComparatorAscendingByAge ageComp;
    customSort(dogs, &ageComp);

    assert(dogs[0].getAge() == 2);
    assert(dogs[1].getAge() == 3);
    assert(dogs[2].getAge() == 5);


}



void Tests::testAll() {
    testMemoryRepository();
    testFileRepository();
    testSQLRepository();
    testAdminService();
    testUserService();
    testDomain();
    testAdoptionList();
    testComparator();
    std::cout << "All tests passed.\n";
}
