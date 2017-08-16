// Program 8.2 - Abstract in-place merge
// Program 8.3 - Top-down mergesort
#ifndef MERGESORT_H
#define MERGESORT_H

// modified from original ACPP version
#include <vector>

template<typename Item_t>
void merge(std::vector<Item_t>& coll, std::vector<Item_t>& aux, int l, int m, int r)
{
    int i;
    for (i = m + 1; i > l; --i) { aux[i - 1] = coll[i - 1]; }

    int j;
    for (j = m; j < r; ++j) { aux[r + m - j] = coll[j + 1]; }

    for (auto k = l; k <= r; ++k) {
        if (aux[j] < aux[i]) { coll[k] = aux[j--]; }
        else { coll[k] = aux[i++]; }
    }
}

template<typename Item_t>
void mergesort(std::vector<Item_t>& coll, std::vector<Item_t>& aux, int l, int r)
{
    if (r <= l) { return; }
    auto m = (r + l) / 2;
    mergesort(coll, aux, l, m);
    mergesort(coll, aux, m + 1, r);
    merge(coll, aux, l, m, r);
}

template<typename Item_t>
void mergesort(std::vector<Item_t>& coll)
{
    std::vector<Item_t> aux;
    aux.reserve(coll.size());
    mergesort(coll, aux, 0, static_cast<int>(coll.size() - 1)); // narrow_cast
}

//template<typename Item_t>
//static void merge(std::vector<Item_t>& a, std::vector<Item_t>& aux, int lo, int mid, int hi)
//{
//    for (auto k = lo; k <= hi; ++k) { aux[k] = a[k]; }
//
//    int i = lo;
//    int j = mid + 1;
//    for (auto k = lo; k <= hi; ++k) {
//        if (i > mid) {
//            a[k] = aux[j++];
//        } else if (j > hi) {
//            a[k] = aux[i++];
//        } else if (aux[j] < aux[i]) {
//            a[k] = aux[j++];
//        } else {
//            a[k] = aux[i++];
//        }
//    }
//}

#endif // MERGESORT_H
