#include "Comparator.h"
#include <algorithm>

void customSort(std::vector<Dog> &dogs, Comparator<Dog> *comp) {
    std::ranges::sort(dogs,
                      [&](const Dog &d1, const Dog &d2) {
                          return comp->compare(d1, d2);
                      });
}
