#include <iostream>
#include <cstdlib>
#include "list.h"

using std::cin;
using std::cout;

int main(int argc, char* argv[])
{
    int i;
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    Node t;
    Node x;
    construct(n);
    for (i = 2, x = new_node(1); i <= n; i++) {
        t = new_node(i);
        insert(x, t);
        x = t;
    }
    while (x != next(x)) {
        for (i = 1; i < m; i++) { x = next(x); }
        delete_node(remove(x));
    }
    cout << item(x) << "\n";
    return 0;
}

