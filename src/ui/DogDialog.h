#pragma once
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialog>

#include "AdminGUI.h"
#include "DogDialog.h"


class DogDialog final : public QDialog {
    Q_OBJECT

private:
    QLineEdit *nameField;
    QLineEdit *breedField;
    QSpinBox *ageField;
    QLineEdit *photoLinkField;

public:
    explicit DogDialog(QWidget *parent = nullptr, const QString &windowTitle = "",
                       const QString &name = "", const QString &breed = "",
                       int age = 0, const QString &photoLink = "");


    [[nodiscard]] QString getName() const { return this->nameField->text(); };
    [[nodiscard]] QString getBreed() const { return this->breedField->text(); };
    [[nodiscard]] int getAge() const { return this->ageField->value(); };
    [[nodiscard]] QString getPhotoLink() const { return this->photoLinkField->text(); };
};
