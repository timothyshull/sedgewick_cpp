#include <iostream>

using std::cin;
using std::cout;

static const int N = 10000;

int main()
{
    int i, p, q, id[N];
    for (i = 0; i < N; i++) { id[i] = i; }
    while (cin >> p >> q) {
        int t = id[p];
        if (t == id[q]) { continue; }
        for (i = 0; i < N; i++) {
            if (id[i] == t) { id[i] = id[q]; }
        }
        cout << " " << p << " " << q << "\n";
    }
    return 0;
}

