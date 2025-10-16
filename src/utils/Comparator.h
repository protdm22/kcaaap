#pragma once

#include <vector>
#include "../domain/Dog.h"
template <typename T>
class Comparator
{
public:
	virtual ~Comparator() = default;

	virtual bool compare(T comp1, T comp2) = 0;
};

class ComparatorAscendingByName final : public Comparator<Dog>
{
public:
	bool compare(const Dog comp1, const Dog comp2) override {
		return comp1.getName() < comp2.getName();
	};
};

class ComparatorAscendingByAge final : public Comparator<Dog>
{
public:
	bool compare(const Dog comp1, const Dog comp2) override {
		return comp1.getAge() < comp2.getAge();
	};
};

void customSort(std::vector<Dog>& dogs, Comparator<Dog>* comp);
