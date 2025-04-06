#include "utilities.h"
#include <cstdlib>
#include <ctime>

int countMean(long long* tab, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += tab[i];
    return sum / size;
}

int* gentab(const int size) {
    int* tab = new int[size];
    srand(time(nullptr));
    for (int i = 0; i < size; i++)
        tab[i] = rand() % 1000000;
    return tab;
}