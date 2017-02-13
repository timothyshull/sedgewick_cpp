#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "STACK.cxx"

inline void push2(STACK<int>& s, int A, int B)
{
    s.push(B);
    s.push(A);
}

template<typename Item>
void quicksort(Item a[], int l, int r)
{
    STACK<int> s(50);
    push2(s, l, r);
    while (!s.empty()) {
        l = s.pop();
        r = s.pop();
        if (r <= l) { continue; }
        int i = partition(a, l, r);
        if (i - l > r - i) {
            push2(s, l, i - 1);
            push2(s, i + 1, r);
        } else {
            push2(s, i + 1, r);
            push2(s, l, i - 1);
        }
    }
}

static const int M = 10;

template<typename Item>
void quicksort(Item a[], int l, int r)
{
    if (r - l <= M) { return; }
    exch(a[(l + r) / 2], a[r - 1]);
    compexch(a[l], a[r - 1]);
    compexch(a[l], a[r]);
    compexch(a[r - 1], a[r]);
    int i = partition(a, l + 1, r - 1);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}

template<typename Item>
void hybridsort(Item a[], int l, int r)
{
    quicksort(a, l, r);
    insertion(a, l, r);
}

template<typename Item>
int operator==(const Item& A, const Item& B) { return !less(A, B) && !less(B, A); }

template<typename Item>
void quicksort(Item a[], int l, int r)
{
    int k;
    Item v = a[r];
    if (r <= l) { return; }
    int i = l - 1, j = r, p = l - 1, q = r;
    for (;;) {
        while (a[++i] < v) {}
        while (v < a[--j]) { if (j == l) { break; }}
        if (i >= j) { break; }
        exch(a[i], a[j]);
        if (a[i] == v) {
            p++;
            exch(a[p], a[i]);
        }
        if (v == a[j]) {
            q--;
            exch(a[q], a[j]);
        }
    }
    exch(a[i], a[r]);
    j = i - 1;
    i = i + 1;
    for (k = l; k <= p; k++, j--) { exch(a[k], a[j]); }
    for (k = r - 1; k >= q; k--, i++) { exch(a[k], a[i]); }
    quicksort(a, l, j);
    quicksort(a, i, r);
}

#endif // QUICKSORT_H
