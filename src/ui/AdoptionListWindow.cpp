#include "AdoptionListWindow.h"
#include <QAbstractItemView>
#include <QVBoxLayout>

AdoptionListWindow::AdoptionListWindow(const UserService &service, QWidget *parent) : QWidget(parent),
    userService(service) {
    setWindowTitle("Adoption List");
    setMinimumSize(450, 300);
    setWindowFlags(Qt::Window);

    dogTable = new DogTable(userService.getAdoptionList(), this);
    table = new QTableView(this);
    table->setModel(dogTable);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setAlternatingRowColors(true);

    const auto layout = new QVBoxLayout(this);
    layout->addWidget(table);
}

void AdoptionListWindow::refresh() const {
    const auto adoptionList = userService.getAdoptionList();
    dogTable->update(adoptionList);
}
