#include "UserGUI.h"
#include "DogDialog.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <QNetworkReply>
#include <QUrl>
#include <QTextBrowser>


void UserGUI::setupUI() {
    const auto mainLayout = new QHBoxLayout(this);

    const auto buttonLayout = new QVBoxLayout();

    const QFont titleFont("Cascadia Code", 18, QFont::Bold);
    title = new QLabel("USER", this);
    title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(titleFont);

    const QFont buttonFont("Verdana", 11, QFont::Normal);
    adoptButton = new QPushButton("Adopt", this);
    skipButton = new QPushButton("Skip", this);
    seeAdoptionListButton = new QPushButton("Open adoption list", this);
    viewAdoptionListButton = new QPushButton("View adoption list", this);
    addFilterButton = new QPushButton("Add filter", this);
    removeFilterButton = new QPushButton("Remove filter", this);

    adoptButton->setFont(buttonFont);
    skipButton->setFont(buttonFont);
    seeAdoptionListButton->setFont(buttonFont);
    viewAdoptionListButton->setFont(buttonFont);
    addFilterButton->setFont(buttonFont);
    removeFilterButton->setFont(buttonFont);

    adoptButton->setFixedSize(140, 35);
    skipButton->setFixedSize(140, 35);
    seeAdoptionListButton->setFixedSize(140, 35);
    viewAdoptionListButton->setFixedSize(140, 35);
    addFilterButton->setFixedSize(140, 35);
    removeFilterButton->setFixedSize(140, 35);

    buttonLayout->addWidget(title);
    buttonLayout->addWidget(adoptButton);
    buttonLayout->addWidget(skipButton);
    buttonLayout->addWidget(seeAdoptionListButton);
    buttonLayout->addWidget(viewAdoptionListButton);
    buttonLayout->addWidget(addFilterButton);
    buttonLayout->addWidget(removeFilterButton);

    mainLayout->addLayout(buttonLayout);

    const auto dogLayout = new QVBoxLayout();

    const QFont dogFont("Jetbrains Mono", 15);
    dogInfoLabel = new QLabel(this);
    dogInfoLabel->setAlignment(Qt::AlignTop);
    dogInfoLabel->setWordWrap(true);
    dogInfoLabel->setFont(dogFont);
    dogLayout->addWidget(dogInfoLabel);

    dogPhotoLabel = new QLabel(this);
    dogPhotoLabel->setFixedSize(250, 250);
    dogPhotoLabel->setAlignment(Qt::AlignCenter);
    dogLayout->addWidget(dogPhotoLabel);

    mainLayout->addLayout(dogLayout);

    adoptionListWindow = nullptr;

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap pix;
            pix.loadFromData(reply->readAll());
            dogPhotoLabel->setPixmap(pix.scaled(dogPhotoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            dogPhotoLabel->setText("Failed to load image.");
        }
        reply->deleteLater();
    });
}

void UserGUI::connectSignals() {
    connect(adoptButton, &QPushButton::clicked, this, [this]() {
        const auto &dogs = isFilterActive ? filteredDogs : this->service.getAllDogs();
        if (dogs.empty() || !hasAvailableDogs()) return;
        if (const auto &dog = dogs[currentDogIndex]; !this->service.isAdopted(dog)) {
            this->service.addToAdoptionList(dog);
            if (adoptionListWindow && adoptionListWindow->isVisible()) {
                adoptionListWindow->refresh();
            }
        }
        currentDogIndex++;
        showNextDog();
    });

    connect(skipButton, &QPushButton::clicked, this, [this]() {
        if (const auto &dogs = isFilterActive ? filteredDogs : this->service.getAllDogs();
            dogs.empty() || !hasAvailableDogs())
            return;
        currentDogIndex++;
        showNextDog();
    });

    connect(seeAdoptionListButton, &QPushButton::clicked, this, [this]() {
        this->service.saveAdoptionListToFile();
        this->service.openAdoptionListFile();
    });

    connect(addFilterButton, &QPushButton::clicked, this, [this]() {
        showFilterDialog();
    });

    connect(removeFilterButton, &QPushButton::clicked, this, [this]() {
        isFilterActive = false;
        currentDogIndex = 0;
        showNextDog();
    });

    connect(viewAdoptionListButton, &QPushButton::clicked, this, &UserGUI::showAdoptionList);
}


bool UserGUI::hasAvailableDogs() const {
    const auto &dogs = isFilterActive ? filteredDogs : service.getAllDogs();
    return std::ranges::any_of(dogs, [this](const Dog &dog) {
        return !service.isAdopted(dog);
    });
}


void UserGUI::showNextDog() {
    const auto &dogs = isFilterActive ? filteredDogs : this->service.getAllDogs();
    int count = 0;

    if (dogs.empty() || !hasAvailableDogs()) {
        dogInfoLabel->setText("No more dogs available.");
        dogPhotoLabel->clear();
        dogPhotoLabel->setPixmap(QPixmap());
        return;
    }

    while (count < dogs.size()) {
        if (currentDogIndex >= dogs.size())
            currentDogIndex = 0;

        if (const auto &dog = dogs[currentDogIndex]; !this->service.isAdopted(dog)) {
            QString dogInfo;
            dogInfo += "<b>Name:</b> " + QString::fromStdString(dog.getName()) + "<br>";
            dogInfo += "<b>Breed:</b> " + QString::fromStdString(dog.getBreed()) + "<br>";
            dogInfo += "<b>Age:</b> " + QString::number(dog.getAge());

            dogInfoLabel->setText(dogInfo);

            const QUrl url(QString::fromStdString(dog.getPhotoLink()));
            networkManager->get(QNetworkRequest(url));
            return;
        }
        currentDogIndex++;
        count++;
    }
}

void UserGUI::showFilterDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Filter Dogs");

    const auto layout = new QVBoxLayout(&dialog);

    const auto breedEdit = new QLineEdit(&dialog);
    breedEdit->setPlaceholderText("Enter breed");

    const auto ageSpin = new QSpinBox(&dialog);
    ageSpin->setMinimum(1);
    ageSpin->setMaximum(100);
    ageSpin->setValue(1);

    layout->addWidget(new QLabel("Breed:", &dialog));
    layout->addWidget(breedEdit);
    layout->addWidget(new QLabel("Maximum Age:", &dialog));
    layout->addWidget(ageSpin);

    const auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        const std::string breed = breedEdit->text().toStdString();
        const int age = ageSpin->value();

        filteredDogs = service.getFilteredDogs(breed, age);
        isFilterActive = true;
        currentDogIndex = 0;
        showNextDog();
    }
}


void UserGUI::closeEvent(QCloseEvent *event) {
    service.adoptDogs();
    emit goBack();
    QWidget::closeEvent(event);
}

void UserGUI::showAdoptionList() {
    if (!adoptionListWindow) {
        adoptionListWindow = new AdoptionListWindow(this->service, this);
    }
    adoptionListWindow->refresh();
    adoptionListWindow->show();
    adoptionListWindow->raise();
    adoptionListWindow->activateWindow();
}
