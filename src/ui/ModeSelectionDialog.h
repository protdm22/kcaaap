#pragma once
#include <QApplication>
#include <QPushButton>
#include "UserService.h"
#include "AdminService.h"

class ModeSelectionDialog final : public QWidget {
    Q_OBJECT

public:
    ModeSelectionDialog(AdminService &adminService, IRepository &repository, QWidget *parent = nullptr);

private slots:
    void launchAdminGUI();

    void launchUserGUI();

    void paintEvent(QPaintEvent *event) override;

private:
    AdminService &adminService;
    IRepository &repository;
};
