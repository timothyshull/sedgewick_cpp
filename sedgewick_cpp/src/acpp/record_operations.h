// Program 6.13 - Data-type implementation for record items
#ifndef RECORD_OPERATIONS_H
#define RECORD_OPERATIONS_H

#include <iostream>

using std::cin;

static record data[maxN];

static int cnt = 0;

void show(const Item& x) { cout << x.r->name << " " << x.r->num << endl; }

int scan(Item& x)
{
    x.r = &data[cnt++];
    return (cin >> x.r->name >> x.r->num) != 0;
}



#endif // RECORD_OPERATIONS_H
