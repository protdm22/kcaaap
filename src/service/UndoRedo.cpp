#include "UndoRedo.h"

void ActionAdd::executeUndo() {
    repository.remove(repository.find(addedDog));
}

void ActionAdd::executeRedo() {
    repository.add(addedDog);
}

void ActionUpdate::executeUndo() {
    repository.remove(repository.find(newDog));
    repository.add(oldDog);
}

void ActionUpdate::executeRedo() {
    repository.remove(repository.find(oldDog));
    repository.add(newDog);
}

void ActionRemove::executeUndo() {
    repository.add(deletedDog);
}

void ActionRemove::executeRedo() {
    repository.remove(repository.find(deletedDog));
}
