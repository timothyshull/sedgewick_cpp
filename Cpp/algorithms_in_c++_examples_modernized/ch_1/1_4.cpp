#include <iostream>

static const int N = 10000;

using std::cin;
using std::cout;

int main()
{
    int i, j, p, q, id[n], sz[n];
    for (i = 0; i < n; i++) {
        id[i] = i;
        sz[i] = 1;
    }
    while (cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]) {
            id[i] = id[id[i]];
        }
        for (j = q; j != id[j]; j = id[j]) {
            id[j] = id[id[j]];
        }
        if (i == j) { continue; }
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        cout << " " << p << " " << q << "\n";
    }
    return 0;
}
