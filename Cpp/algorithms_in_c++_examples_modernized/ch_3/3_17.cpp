#include <iostream>
#include <cstdlib>
#include <cstring>

using std::cin;
using std::cout;

int compare(const void* i, const void* j) { return strcmp(*(char**) i, *(char**) j); }

int main(int argc, char* argv[])
{
    const int n_max = 1000;
    const int m_max = 10000;
    char* a[n_max];
    int n;
    char buf[m_max];
    int m = 0;
    for (n = 0; n < n_max; n++) {
        a[n] = &buf[m];
        if (!(cin >> a[n])) { break; }
        m += strlen(a[n]) + 1;
    }
    qsort(a, n, sizeof(char*), compare);
    for (int i = 0; i < n; i++) {
        cout << a[i] << "\n";
    }
    return 0;
}

