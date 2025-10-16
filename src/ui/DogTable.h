#pragma once
#include <QAbstractTableModel>

#include "Dog.h"


class DogTable final : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Dog> dogs;

    void clear();

public:
    explicit DogTable(const std::vector<Dog> &dogs,
                      QObject *parent = nullptr) : QAbstractTableModel(parent), dogs(dogs) {
    };

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void update(const std::vector<Dog> &newDogs);
};
