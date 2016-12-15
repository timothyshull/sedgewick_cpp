template<class Item>
int partition(Item a[], int l, int r) {
    int i = l - 1, j = r;
    Item v = a[r];
    for (;;) {
        while (a[++i] < v) {}
        while (v < a[--j]) { if (j == l) { break; }}
        if (i >= j) { break; }
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}