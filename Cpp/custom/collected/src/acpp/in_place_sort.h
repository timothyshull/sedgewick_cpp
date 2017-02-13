// Program 6.14 - In-place sort
#ifndef IN_PLACE_SORT_H
#define IN_PLACE_SORT_H

template<class Item>
void insitu(Item data[], Index a[], int N)
{
    for (int i = 0; i < N; i++) {
        Item v = data[i];
        int j, k;
        for (k = i; a[k] != i; k = a[j], a[j] = j) {
            j = k;
            data[k] = data[a[k]];
        }
        data[k] = v;
        a[k] = k;
    }
}

#endif // IN_PLACE_SORT_H
