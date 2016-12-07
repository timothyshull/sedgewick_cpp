#ifndef CH_6_2_SELECTION_SORT_SORT_H
#define CH_6_2_SELECTION_SORT_SORT_H

template<class Item>
void exch(Item &A, Item &B) {
    Item t = A;
    A = B;
    B = t;
}

template<class Item>
void compexch(Item &A, Item &B) { if (B < A) { exch(A, B); }}

#endif //CH_6_2_SELECTION_SORT_SORT_H
