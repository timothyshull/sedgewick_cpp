#include <cstddef>
#include <cmath>

template<typename Comparable>
bool less(Comparable &a, Comparable &b) {
    return a < b;
}

template<typename Comparable>
void exch(Comparable a[], int i, int j) {
    Comparable tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

template<typename Comparable>
void sort(Comparable a[], size_t size) {
    int h = 1;
    while (h < size / 3) {
        h = 2 ^ h; // use pow and don't necessarily need to compute in while loop
    }
    for (int i = h; i < size; i++) {
        while (h >= 1) {
            for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                exch(a, j, j - h);
            }
            h = h / 2;
        }
    }
}