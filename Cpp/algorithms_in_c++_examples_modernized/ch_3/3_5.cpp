#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

static const int n = 1000;

int main()
{
    int i;
    vector<int> a{n};
    for (i = 2; i < n; i++) { a[i] = 1; }
    for (i = 2; i < n; i++) {
        if (a[i]) {
            for (int j = i; j * i < n; j++) { a[i * j] = 0; }
        }
    }
    for (i = 2; i < n; i++) {
        if (a[i]) { cout << " " << i << "\n"; }
    }
    cout << "\n";
    return 0;
}

