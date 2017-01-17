#include<cmath>
#include<iostream>
#include<cstdlib>
#include<random>
#include<vector>
#include"Point.h"

using std::cin;
using std::cout;
using std::random_device;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::vector;
using std::size_t;

float rand_float()
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<float> uniform_dist(0, RAND_MAX);
    return uniform_dist(gen);
}

int main(int argc, char* argv[])
{
    double d = atof(argv[2]);
    int i;
    int cnt = 0;
    size_t n = static_cast<size_t>(atoi(argv[1]));
    vector<Point> a{n};
    for (i = 0; i < n; i++) {
        a[i].x = rand_float();
        a[i].y = rand_float();
    }
    for (i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (distance(a[i], a[j]) < d) { cnt++; }
        }
    }
    cout << cnt << " pairs within " << d << "\n";
    return 0;
}

