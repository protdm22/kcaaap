#include <iostream>

#include "ui/AdminGUI.h"
#include "ui/UserGUI.h"

#include "repository/MemoryRepository.h"
#include "repository/FileRepository.h"
#include "repository/SQLRepository.h"

#include "FileAdoptionList.h"
#include "ModeSelectionDialog.h"
#include "../tests/Tests.h"

#include "utils/GeneratorUtils.h"


int main(int argc, char *argv[]) {
    Tests::testAll();

    std::unique_ptr<IRepository> repository;
    // repository = std::make_unique<MemoryRepository>();
    // repository = std::make_unique<FileRepository>("dogs.txt");
    repository = std::make_unique<SQLRepository>("dogs.db");

    AdminService adminService{repository.get()};

    if (repository->size() == 0) {
        std::cout << "Repository is empty. Generating initial entries...\n";
        GeneratorUtils::initializeEntries(&adminService);
    }

    QApplication qtApp(argc, argv);
    ModeSelectionDialog selector(adminService, *repository);
    selector.show();
    return qtApp.exec();
}
