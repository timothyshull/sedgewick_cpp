#include "Quick_union_uf.h"

Quick_union_uf::Quick_union_uf(int n)
{
    parent = new int[n];
    count = n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int Quick_union_uf::count()
{
    return count;
}

int Quick_union_uf::find(int p)
{
    validate(p);
    while (p != parent[p])
        p = parent[p];
    return p;
}

bool Quick_union_uf::connected(int p, int q)
{
    return find(p) == find(q);
}

void Quick_union_uf::create_union(int p, int q)
{
    int rootP = find(p);
    int rootQ = find(q);
    if (rootP == rootQ) return;
    parent[rootP] = rootQ;
    count--;
}

void Quick_union_uf::validate(int p)
{
    int n = parent.length;
    if (p < 0 || p >= n) {
        throw new IndexOutOfBoundsException("index " + p + " is not between 0 and " + (n - 1));
    }
}
