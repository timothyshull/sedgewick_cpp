// Program 3.16 - Two-dimensional array allocation
#include "2d_array_allocation.h"

int** malloc2d(int rows, int columns)
{
    int** a{new int* [rows]};
    for (auto i = 0; i < rows; ++i) {
        a[i] = new int[columns];
    }
    return a;
}

// contiguous 1
//int** malloc2d(int rows, int columns)
//{
//    int** a{new int* [rows]};
//    int* pool{new int[rows][columns]};
//    for (auto i = 0; i < rows; ++i, pool += columns) {
//        a[i] = pool;
//    }
//    return a;
//}

// contiguous 2 ?
// int** malloc2d(int rows, int columns) { return new int*[rows][columns]; }