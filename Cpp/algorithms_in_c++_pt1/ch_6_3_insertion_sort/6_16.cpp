#include "sort.h"

template<class Item>
void insertion(Item a[], int l, int r) {
    int i, j;

    for (i = l + 1; i <= r; i++) {
        j = i;

        while (j > 0 && a[j] < a[j - 1]) {
            Item tmp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = tmp;
            j--;
        }
    }
}