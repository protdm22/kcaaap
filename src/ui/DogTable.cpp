#include "DogTable.h"

int DogTable::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(dogs.size());
}

int DogTable::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant DogTable::data(const QModelIndex &index, const int role) const {
    if (!index.isValid() || index.row() >= static_cast<int>(dogs.size())) {
        return QVariant();
    }
    const auto &dog = dogs[index.row()];
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: return QVariant(QString::fromStdString(dog.getName()));
            case 1: return QVariant(QString::fromStdString(dog.getBreed()));
            case 2: return QVariant(dog.getAge());
            case 3: return QVariant(QString::fromStdString(dog.getPhotoLink()));
            default: return QVariant();
        }
    }
    return QVariant();
}

QVariant DogTable::headerData(const int section, const Qt::Orientation orientation, const int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "Name";
            case 1: return "Breed";
            case 2: return "Age";
            case 3: return "Photo Link";
            default: return QVariant();
        }
    }
    return QVariant();
}

void DogTable::clear() {
    beginResetModel();
    dogs.clear();
    endResetModel();
}

void DogTable::update(const std::vector<Dog> &newDogs) {
    beginResetModel();
    dogs = newDogs;
    endResetModel();
}
