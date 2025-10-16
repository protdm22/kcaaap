#include "ListTypeSelectionDialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

ListTypeSelectionDialog::ListTypeSelectionDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Select adoption list type");
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Which type of adoption list would you like?"));

    auto *CSVButton = new QPushButton("CSV");
    auto *HTMLButton = new QPushButton("HTML");

    layout->addWidget(CSVButton);
    layout->addWidget(HTMLButton);

    connect(CSVButton, &QPushButton::clicked, this, &ListTypeSelectionDialog::chooseCSV);
    connect(HTMLButton, &QPushButton::clicked, this, &ListTypeSelectionDialog::chooseHTML);
}

void ListTypeSelectionDialog::chooseCSV() {
    selectedType = CSV;
    accept();
}

void ListTypeSelectionDialog::chooseHTML() {
    selectedType = HTML;
    accept();
}

ListTypeSelectionDialog::ListType ListTypeSelectionDialog::getType() const {
    return selectedType;
}
