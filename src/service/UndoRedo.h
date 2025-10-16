#pragma once
#include "IRepository.h"
#include "Dog.h"


class Action {
public:
    Action() {
    };

    virtual ~Action() = default;

    virtual void executeUndo() = 0;

    virtual void executeRedo() = 0;
};

class ActionAdd final : public Action {
private:
    Dog addedDog;
    IRepository &repository;

public:
    ActionAdd(const Dog &dog, IRepository &repository) : addedDog(dog), repository(repository) {
    };

    ~ActionAdd() override = default;

    void executeUndo() override;

    void executeRedo() override;
};

class ActionUpdate final : public Action {
private:
    Dog oldDog, newDog;
    IRepository &repository;

public:
    ActionUpdate(const Dog &oldDog, const Dog &newDog, IRepository &repository) : oldDog(oldDog), newDog(newDog),
        repository(repository) {
    }

    ~ActionUpdate() override = default;

    void executeUndo() override;

    void executeRedo() override;
};

class ActionRemove final : public Action {
private:
    Dog deletedDog;
    IRepository &repository;

public:
    ActionRemove(const Dog &dog, IRepository &repository) : deletedDog(dog), repository(repository) {
    };

    ~ActionRemove() override = default;

    void executeUndo() override;

    void executeRedo() override;
};
