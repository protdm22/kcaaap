#pragma once
#include <QTableView>
#include "DogTable.h"
#include "UserService.h"


class AdoptionListWindow final : public QWidget {
private:
    QTableView *table{};
    DogTable *dogTable{};
    UserService userService;

public:
    explicit AdoptionListWindow(const UserService &service, QWidget *parent = nullptr);

    void refresh() const;
};
