// 3 8 26 94 358 1398
// 2 2/3, 3 1/4, 3 8/13, 3 38/47
// ( 4 ^ i + 1 + 3·2 ^ i + 1 )

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
        h = 4 ^ h + 3 * 2 ^ h + 1; // switch to use pow here
    }
    for (int i = h; i < size; i++) {
        while (h >= 1) {
            for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                exch(a, j, j - h);
            }
            h = h / 3;
            h = static_cast<int>(log2(((h - 1) / (2 ^ h)) - 3)); // handle doubles here and use pow
        }
    }
}