#include "AdminGUI.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>

#include "DogDialog.h"
#include "../exceptions/ServiceException.h"

void AdminGUI::setupUI() {
    const auto mainLayout = new QHBoxLayout(this);

    const auto buttonLayout = new QVBoxLayout();

    const QFont titleFont("Cascadia Code", 18, QFont::Bold);
    title = new QLabel("ADMIN", this);
    title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(titleFont);

    viewMode = new QComboBox(this);
    viewMode->addItem("Short");
    viewMode->addItem("Detailed");

    const QFont buttonFont("Verdana", 12, QFont::Normal);
    addDogButton = new QPushButton("Add", this);
    updateDogButton = new QPushButton("Update", this);
    deleteDogButton = new QPushButton("Delete", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);

    undoShortcut = new QShortcut(QKeySequence::Undo, this);
    redoShortcut = new QShortcut(QKeySequence::Redo, this);

    addDogButton->setFont(buttonFont);
    updateDogButton->setFont(buttonFont);
    deleteDogButton->setFont(buttonFont);
    undoButton->setFont(buttonFont);
    redoButton->setFont(buttonFont);

    const QFont comboBoxFont("Verdana", 10, QFont::Normal);
    viewMode->setFont(comboBoxFont);

    addDogButton->setFixedSize(80, 35);
    updateDogButton->setFixedSize(80, 35);
    deleteDogButton->setFixedSize(80, 35);
    undoButton->setFixedSize(80, 35);
    redoButton->setFixedSize(80, 35);

    buttonLayout->addWidget(title);
    buttonLayout->addWidget(viewMode);
    buttonLayout->addWidget(addDogButton);
    buttonLayout->addWidget(updateDogButton);
    buttonLayout->addWidget(deleteDogButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);

    mainLayout->addLayout(buttonLayout);

    const QFont listFont("Jetbrains Mono", 11);
    dogList = new QListWidget(this);
    dogList->setFont(listFont);

    mainLayout->addWidget(dogList);

    setMinimumSize(600, 300);
}

void AdminGUI::connectSignals() {
    connect(addDogButton, &QPushButton::clicked, this, [this]() {
        if (DogDialog addDialog(this, "Add a new dog"); addDialog.exec() == QDialog::Accepted) {
            const std::string name = addDialog.getName().toStdString();
            const std::string breed = addDialog.getBreed().toStdString();
            const int age = addDialog.getAge();
            const std::string photoLink = addDialog.getPhotoLink().toStdString();
            try {
                service.addDog(name, breed, age, photoLink);
                this->refreshDogList();
            } catch (std::exception &e) {
                QMessageBox::warning(this, "Invalid dog data", e.what());
            }
        }
    });

    connect(updateDogButton, &QPushButton::clicked, this, [this]() {
        const int row = dogList->currentRow();
        const auto dogs = this->service.getAllDogs();

        if (row < 0 || row >= dogs.size()) {
            QMessageBox::warning(this, "Nothing selected", "Please select a dog to update");
            return;
        }
        const auto &selectedDog = dogs[row];

        if (DogDialog updateDialog(this, "Add a new dog", (selectedDog.getName().data()),
                                   (selectedDog.getBreed().data()),
                                   selectedDog.getAge(),
                                   (selectedDog.getPhotoLink().data())); updateDialog.exec() == QDialog::Accepted) {
            const std::string name = updateDialog.getName().toStdString();
            const std::string breed = updateDialog.getBreed().toStdString();
            const std::string age = std::to_string(updateDialog.getAge());
            const std::string photoLink = updateDialog.getPhotoLink().toStdString();
            try {
                service.updateDog(service.findDog(selectedDog.getName(), selectedDog.getBreed(), selectedDog.getAge()),
                                  name, breed, age, photoLink);
                this->refreshDogList();
            } catch (std::exception &e) {
                QMessageBox::warning(this, "Invalid dog data", e.what());
            }
        }
    });

    connect(deleteDogButton, &QPushButton::clicked, this, [this]() {
        const int row = dogList->currentRow();
        const auto dogs = this->service.getAllDogs();

        if (row < 0 || row >= dogs.size()) {
            QMessageBox::warning(this, "Nothing selected", "Please select a dog to delete");
            return;
        }
        const auto &selectedDog = dogs[row];
        service.removeDog(selectedDog.getName(), selectedDog.getBreed(), selectedDog.getAge());
        this->refreshDogList();
    });

    connect(viewMode, &QComboBox::currentTextChanged, this, &AdminGUI::refreshDogList);

    connect(undoButton, &QPushButton::clicked, this, &AdminGUI::handleUndo);
    connect(undoShortcut, &QShortcut::activated, this, &AdminGUI::handleUndo);

    connect(redoButton, &QPushButton::clicked, this, &AdminGUI::handleRedo);
    connect(redoShortcut, &QShortcut::activated, this, &AdminGUI::handleRedo);
}

void AdminGUI::refreshDogList() const {
    dogList->clear();
    const bool isShort = viewMode->currentText() == "Short";
    for (const auto &dog: this->service.getAllDogs()) {
        std::stringstream ss;
        if (isShort)
            ss << dog.getName();
        else
            ss << dog;
        dogList->addItem(QString::fromStdString(ss.str()));
    }
}

void AdminGUI::closeEvent(QCloseEvent *event) {
    emit goBack();
    QWidget::closeEvent(event);
}

void AdminGUI::handleUndo() {
    try {
        this->service.undo();
    } catch (ServiceException &e) {
        QMessageBox::warning(this, "Undo error", e.what());
    }
    this->refreshDogList();
}

void AdminGUI::handleRedo() {
    try {
        this->service.redo();
    } catch (ServiceException &e) {
        QMessageBox::warning(this, "Redo error", e.what());
    }
    this->refreshDogList();
}
