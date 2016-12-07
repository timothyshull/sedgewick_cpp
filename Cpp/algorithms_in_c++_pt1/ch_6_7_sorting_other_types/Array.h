#ifndef CH_6_7_SORTING_OTHER_TYPES_ARRAY_H
#define CH_6_7_SORTING_OTHER_TYPES_ARRAY_H

template<class Item>
void rand(Item a[], int N) { for (int i = 0; i < N; i++) { rand(a[i]); }}

template<class Item>
void scan(Item a[], int &N) {
    for (int i = 0; i < N; i++) {
        if (!scan(a[i])) { break; }
    }
    N = i;
}

template<class Item>
void show(Item a[], int l, int r) {
    for (int i = l; i <= r; i++) {
        show(a[i]);
    }
    cout << endl;
}

template<class Item>
void sort(Item a[], int l, int r);

#endif //CH_6_7_SORTING_OTHER_TYPES_ARRAY_H
