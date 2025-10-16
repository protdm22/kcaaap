#pragma once
#include <QDialog>


class ListTypeSelectionDialog final : public QDialog {
    Q_OBJECT

public:
    enum ListType { CSV, HTML, NONE };

    explicit ListTypeSelectionDialog(QWidget *parent = nullptr);

    [[nodiscard]] ListType getType() const;

private:
    ListType selectedType = NONE;

private slots:
    void chooseCSV();

    void chooseHTML();
};
