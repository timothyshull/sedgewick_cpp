// Program 7.1 - Quicksort
// Program 7.2 - Partitioning
// Program 7.3 - Nonrecursive quicksort
// Program 7.4 - Improved quicksort
// Program 7.5 - Quicksort with three-way partitioning

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <stack>

// utility function
template<typename Item_type>
inline void comp_exch(std::vector<Item_type>& coll, int index_a, int index_b) { if (coll[index_b] < coll[index_a]) { std::swap(coll[index_a], coll[index_b]); }}

// basic -> combination of AJ and ACPP
template<typename Item_type>
int partition(std::vector<Item_type>& coll, int l, int r)
{
    auto i = l;
    auto j = r + 1;

    Item_type v{coll[l]};
    while (true) {
        while (coll[++i] < v) { if (i == r) { break; }}
        while (v < coll[--j]) { if (j == l) { break; }}
        if (i >= j) { break; }
        std::swap(coll[i], coll[j]);
    }
    std::swap(coll[l], coll[j]);
    return j;
}

template<class Item_type>
void quicksort(std::vector<Item_type>& coll, int l, int r)
{
    if (r <= l) { return; }
    auto i = partition(coll, l, r);
    quicksort(coll, l, i - 1);
    quicksort(coll, i + 1, r);
}

template<class Item_type>
inline void quicksort(std::vector<Item_type>& coll) { quicksort(coll, 0, static_cast<int>(coll.size() - 1)); }

// Non-recursive
inline void push2(std::stack<int>& s, int a, int b)
{
    s.push(b);
    s.push(a);
}

template<class Item_type>
void iterative_quicksort(std::vector<Item_type>& coll, int l, int r)
{
    std::stack<int> s;
    push2(s, l, r);
    int i;
    while (!s.empty()) {
        l = s.top();
        s.pop();
        r = s.top();
        s.pop();

        if (r <= l) { continue; }
        i = partition(coll, l, r);
        if (i - l > r - i) {
            push2(s, l, i - 1);
            push2(s, i + 1, r);
        } else {
            push2(s, i + 1, r);
            push2(s, l, i - 1);
        }
    }
}


// improved quicksort - median-of-3
template<class Item_type>
void insertion_sort(std::vector<Item_type>& coll, int l, int r)
{
    int i;
    for (i = r; i > l; --i) {
        if (coll[i] < coll[i - 1]) { std::swap(coll[i - 1], coll[i]); }
    }
    for (i = l + 2; i <= r; ++i) {
        auto j = i;
        Item_type v = coll[i];
        while (v < coll[j - 1]) {
            coll[j] = coll[j - 1];
            --j;
        }
        coll[j] = v;
    }
}

template<class Item_type>
void quicksort_m3(std::vector<Item_type>& coll, int l, int r)
{
    static const auto cutoff = 10;
    if (r - l <= cutoff) { return; }
    std::swap(coll[(l + r) / 2], coll[r - 1]);
    comp_exch(coll, l, r - 1);
    comp_exch(coll, l, r);
    comp_exch(coll, r - 1, r);

    auto i = partition(coll, l + 1, r - 1);
    quicksort_m3(coll, l, i - 1);
    quicksort_m3(coll, i + 1, r);
}

template<class Item_type>
void hybridsort(std::vector<Item_type>& coll, int l, int r)
{
    quicksort_m3(coll, l, r);
    insertion_sort(coll, l, r);
}



// quicksort with 3-way partitioning
template<class Item_type>
void quicksort_3_way(std::vector<Item_type>& coll, int l, int r)
{
    int k;
    Item_type v{coll[r]};
    if (r <= l) { return; }

    auto i = l - 1;
    auto j = r;
    auto p = l - 1;
    auto q = r;

    for (;;) {
        while (coll[++i] < v) {}
        while (v < coll[--j]) { if (j == l) { break; }}
        if (i >= j) { break; }

        std::swap(coll[i], coll[j]);
        if (coll[i] == v) {
            ++p;
            std::swap(coll[p], coll[i]);
        }
        if (v == coll[j]) {
            --q;
            std::swap(coll[q], coll[j]);
        }
    }

    std::swap(coll[i], coll[r]);

    j = i - 1;
    i = i + 1;
    for (k = l; k <= p; ++k, --j) { std::swap(coll[k], coll[j]); }
    for (k = r - 1; k >= q; --k, ++i) { std::swap(coll[k], coll[i]); }

    quicksort_3_way(coll, l, j);
    quicksort_3_way(coll, i, r);
}

#endif // QUICKSORT_H
