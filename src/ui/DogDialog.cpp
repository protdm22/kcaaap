#include "DogDialog.h"

#include <qdialogbuttonbox.h>
#include <Windows.h>

DogDialog::DogDialog(QWidget *parent, const QString &windowTitle, const QString &name, const QString &breed,
                     const int age, const QString &photoLink) {
    setWindowTitle(windowTitle);

    const auto layout = new QFormLayout(this);

    nameField = new QLineEdit(name, this);
    breedField = new QLineEdit(breed, this);
    ageField = new QSpinBox(this);
    ageField->setValue(age);
    ageField->setRange(0, 40);
    photoLinkField = new QLineEdit(photoLink, this);

    layout->addRow("Name: ", nameField);
    layout->addRow("Breed: ", breedField);
    layout->addRow("Age: ", ageField);
    layout->addRow("Photo link: ", photoLinkField);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    adjustSize();
}
