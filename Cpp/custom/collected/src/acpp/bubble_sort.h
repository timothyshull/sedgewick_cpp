// Program 6.4 - Bubble sort
#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

template<class Item>
void bubble(Item a[], int l, int r)
{
    for (int i = l; i < r; i++) {
        for (int j = r; j > i; j--) {
            compexch(a[j - 1], a[j]);
        }
    }
}

#endif // BUBBLE_SORT_H
