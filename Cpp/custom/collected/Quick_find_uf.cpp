#include "Quick_find_uf.h"

Quick_find_uf::Quick_find_uf(int n)
{
    count = n;
    id = new int[n];
    for (int i{0}; i < n; ++i)
        id[i] = i;
}

int Quick_find_uf::count()
{
    return count;
}

int Quick_find_uf::find(int p)
{
    validate(p);
    return id[p];
}

bool Quick_find_uf::connected(int p, int q)
{
    validate(p);
    validate(q);
    return id[p] == id[q];
}

void Quick_find_uf::create_union(int p, int q)
{
    validate(p);
    validate(q);
    int pID = id[p];   // needed for correctness
    int qID = id[q];   // to reduce the number of array accesses

    // p and q are already _in the same component
    if (pID == qID) return;

    for (int i{0}; i < id.length; ++i)
        if (id[i] == pID) id[i] = qID;
    count--;
}

void Quick_find_uf::validate(int p)
{
    int n = id.length;
    if (p < 0 || p >= n) {
        throw new IndexOutOfBoundsException("index " + p + " is not between 0 and " + (n - 1));
    }
}
