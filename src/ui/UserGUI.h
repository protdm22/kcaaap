#pragma once
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QNetworkAccessManager>

#include "AdoptionListWindow.h"
#include "UserService.h"

class UserGUI final : public QWidget {
    Q_OBJECT

private:
    UserService &service;

    QLabel *title{};
    QPushButton *adoptButton{};
    QPushButton *skipButton{};
    QPushButton *seeAdoptionListButton{};
    QPushButton *viewAdoptionListButton{};
    QPushButton *addFilterButton{};
    QPushButton *removeFilterButton{};

    QLabel *dogInfoLabel;
    QLabel *dogPhotoLabel;

    QNetworkAccessManager *networkManager;

    AdoptionListWindow *adoptionListWindow;

    int currentDogIndex = 0;
    bool isFilterActive = false;
    std::vector<Dog> filteredDogs;

    void setupUI();

    void connectSignals();

    void showFilterDialog();

    bool hasAvailableDogs() const;

    void showNextDog();

public:
    explicit UserGUI(UserService &service, QWidget *parent = nullptr)
        : QWidget(parent), service(service) {
        setupUI();
        connectSignals();
        showNextDog();
    }

signals:
    void goBack();

private slots:
    void showAdoptionList();

protected:
    void closeEvent(QCloseEvent *event) override;
};
