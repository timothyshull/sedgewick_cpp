#include<iostream>

using std::cin;
using std::cout;

static const int N = 10000;

int main()
{
    int i, j, p, q, id[n];
    for (i = 0; i < n; i++) { id[i] = i; }
    while (cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]) {}
        for (j = q; j != id[j]; j = id[j]) {}
        if (i == j) { continue; }
        id[i] = j;
        cout << " " << p << " " << q << "\n";
    }
    return 0;
}