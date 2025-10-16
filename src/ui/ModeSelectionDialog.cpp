#include "ModeSelectionDialog.h"
#include "AdminGUI.h"
#include "UserGUI.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>

#include "ListTypeSelectionDialog.h"

ModeSelectionDialog::ModeSelectionDialog(AdminService &adminService, IRepository &repository, QWidget *parent)
    : QWidget(parent), adminService(adminService), repository(repository) {
    setWindowTitle("Choose Mode");


    auto *title = new QLabel("Keep calm and adopt a pet", this);
    auto *ask = new QLabel("Choose an option:", this);

    const QFont titleFont("Cascadia Code", 20, QFont::Bold);
    const QFont askFont("Cascadia Code", 14, QFont::Normal);
    title->setFont(titleFont);
    ask->setFont(askFont);
    title->setAlignment(Qt::AlignCenter);
    ask->setAlignment(Qt::AlignCenter);

    auto *adminButton = new QPushButton("Admin", this);
    auto *userButton = new QPushButton("User", this);

    const QFont buttonFont("Verdana", 14, QFont::Normal);
    adminButton->setFont(buttonFont);
    userButton->setFont(buttonFont);

    adminButton->setFixedSize(110, 40);
    userButton->setFixedSize(110, 40);

    auto *layout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout(this);

    layout->addWidget(title);
    layout->addWidget(ask);
    buttonLayout->addWidget(adminButton);
    buttonLayout->addWidget(userButton);
    layout->addLayout(buttonLayout);

    connect(adminButton, &QPushButton::clicked, this, &ModeSelectionDialog::launchAdminGUI);
    connect(userButton, &QPushButton::clicked, this, &ModeSelectionDialog::launchUserGUI);

    setMinimumSize(200, 150);
}

void ModeSelectionDialog::launchAdminGUI() {
    auto *adminGUI = new AdminGUI(adminService);

    connect(adminGUI, &AdminGUI::goBack, this, [this,adminGUI]() {
        this->show();
        adminGUI->close();
    });

    adminGUI->show();
    this->close();
}

void ModeSelectionDialog::launchUserGUI() {
    if (ListTypeSelectionDialog dialog(this); dialog.exec() == QDialog::Accepted) {
        const auto type = dialog.getType();

        std::shared_ptr<FileAdoptionList> adoptionList;
        if (type == ListTypeSelectionDialog::CSV)
            adoptionList = std::make_shared<CSVAdoptionList>("adoption-list.csv");
        else
            adoptionList = std::make_shared<HTMLAdoptionList>("adoption-list.html");

        const auto userService = std::make_shared<UserService>(&repository, *adoptionList);
        auto *userGUI = new UserGUI(*userService);

        userGUI->setAttribute(Qt::WA_DeleteOnClose);
        userGUI->show();

        connect(userGUI, &UserGUI::goBack, this, [this, userGUI, adoptionList, userService]() {
            this->show();
            userGUI->close();
        });

        this->close();
    }
}

void ModeSelectionDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
    gradient.setColorAt(0, QColor(50,50,50));
    gradient.setColorAt(1,QColor(140,140,140));
    painter.fillRect(rect(),gradient);
    QWidget::paintEvent(event);
}
