#pragma once
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include "AdminService.h"
#include <QComboBox>

class AdminGUI final : public QWidget {
    Q_OBJECT

private:
    AdminService &service;

    QComboBox *viewMode{};
    QLabel *title{};
    QListWidget *dogList{};
    QPushButton *addDogButton{};
    QPushButton *updateDogButton{};
    QPushButton *deleteDogButton{};
    QPushButton *undoButton{};
    QPushButton *redoButton{};
    QShortcut *undoShortcut{};
    QShortcut *redoShortcut{};

    void setupUI();

    void connectSignals();

    void refreshDogList() const;

    void handleUndo();

    void handleRedo();

public:
    explicit AdminGUI(AdminService &service, QWidget *parent = nullptr)
        : QWidget(parent), service(service) {
        setupUI();
        connectSignals();
        refreshDogList();
    }

signals:
    void goBack();

protected:
    void closeEvent(QCloseEvent *event) override;
};
