// Program 6.11 - Data-type implementation for string items
// Program 6.12 - Data-type interface for record items
// Program 6.13 - Data-type implementation for record items
#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Item.h"

using std::cin;
using std::cout;

static char buf[100000];

static int cnt = 0;

int operator<(const Item& a, const Item& b) { return strcmp(a.str, b.str) < 0; }

void show(const Item& x) { cout << x.str << " "; }

int scan(Item& x)
{
    int flag = (cin >> (x.str = &buf[cnt])) != 0;
    cnt += strlen(x.str) + 1;
    return flag;
}

#endif // STRING_OPERATIONS_H
