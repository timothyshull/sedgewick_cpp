#include "sort.h"

// uses optimizations to improve performance
template<class Item>
void insertion(Item a[], int l, int r) {
    int i;
    for (i = r; i > l; i--) { compexch(a[i - 1], a[i]); } // makes sure min is in index 0
    for (i = l + 2; i <= r; i++) {
        int j = i;
        /*
         * tightens the while loop by removing the creation of temporary value
         * we know this works because each pass through the loop knows the lowest
         * values are already sorted and if v is less than the element immediately below
         * it can be exchanged, if it is less than more it well get moved down to index 1,
         * and it can break when it is not less because all lower indices are already sorted
         */
        Item v = a[i];
        while (v < a[j - 1]) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

// orig C++
//template<class Item>
//void sort(Item a[], int l, int r) {
//    for (int i = l + 1; i <= r; i++) {
//        for (int j = i; j > l; j--) {
//            compexch(a[j - 1], a[j]);
//        }
//    }
//}

// online
//void insertion_sort(int arr[], int length) {
//    int j, temp;
//
//    for (int i = 0; i < length; i++) {
//        j = i;
//
//        while (j > 0 && arr[j] < arr[j - 1]) {
//            temp = arr[j];
//            arr[j] = arr[j - 1];
//            arr[j - 1] = temp;
//            j--;
//        }
//    }
//}

// Java version
//template<typename Comparable>
//void sort(Comparable a[], int N) {  // Sort a[] into increasing order.
//    for (int i = 1; i < N; i++) {  // Insert a[i] among a[i-1], a[i-2], a[i-3]... ..
//        for (int j = i; j > 0 && less(a[j], a[j - 1]); j--) {
//            exch(a, j, j - 1);
//        }
//    }
//}

