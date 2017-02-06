#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>

using std::cin;
using std::cout;
using std::vector;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;

bool heads()
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> uniform_dist(0, RAND_MAX);
    return uniform_dist(gen) < RAND_MAX / 2;
}

int main(int argc, char* argv[])
{
    int i;
    int j;
    int cnt;
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    vector<int> f{n + 1, 0};
    for (i = 0; i < m; i++, f[cnt]++) {
        for (cnt = 0, j = 0; j <= n; j++) {
            if (heads()) { cnt++; }
        }
    }
    for (j = 0; j <= n; j++) {
        if (f[j] == 0) { cout << "."; }
        for (i = 0; i < f[j]; i += 10) { cout << "*"; }
        cout << "\n";
    }
    return 0;
}

