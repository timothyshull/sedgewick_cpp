#include "sort.h"

template<class Item>
void bubble(Item a[], int l, int r) {
    for (int i = l; i < r; i++) {
        for (int j = r; j > i; j--) {
            if (a)
            compexch(a[j - 1], a[j]);
        }
    }
}