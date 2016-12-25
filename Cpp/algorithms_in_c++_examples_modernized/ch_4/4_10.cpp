#include <iostream>
#include <stdlib.h>
#include "UF.cxx"

int main(int argc, char* argv[])
{
    int p, q, N = atoi(argv[1]);
    UF info(N);
    while (cin >> p >> q) {
        if (!info.find(p, q)) {
            info.unite(p, q);
            cout << " " << p << " " << q << "\n";
        }
    }
}

