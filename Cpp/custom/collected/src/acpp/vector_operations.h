// Program 6.7 - Interface for array data type
// Program 6.8 - Implementation of array data type
// Program 6.9 - Sample for item data type
// Program 6.10 - Sample implementation for item data type
#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

#include <iostream>
#include <cstdlib>
#include "Array.h"

using std::cin;
using std::cout;

template<typename Item>
void rand(Item a[], int N) { for (int i = 0; i < N; i++) { rand(a[i]); }}

template<typename Item>
void scan(Item a[], int& N)
{
    for (int i = 0; i < N; i++) {
        if (!scan(a[i])) { break; }
    }
    N = i;
}

template<typename Item>
void show(Item a[], int l, int r)
{
    for (int i = l; i <= r; i++) {
        show(a[i]);
    }
    cout << endl;
}

#include <iostream>
#include <cstdlib>
#include "Item.h"

using std::cin;
using std::cout;

int operator<(const Item& A, const Item& B) { return A.key < B.key; }

int scan(Item& x) { return (cin >> x.key >> x.info) != 0; }

void rand(Item& x)
{
    x.key = 1000 * (1.0 * rand() / RAND_MAX);
    x.info = 1.0 * rand() / RAND_MAX;
}

void show(const Item& x) { cout << x.key << " " << x.info << endl; }

#endif // VECTOR_OPERATIONS_H
