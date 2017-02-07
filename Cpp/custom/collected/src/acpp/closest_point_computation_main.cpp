// Program 3.8 - Closest point computation
#include <cmath>
#include <iostream>
#include <random>
#include "Point.h"

//float rand_float()
//{
//    std::random_device rd;
//    std::default_random_engine gen{rd()};
//    std::uniform_real_distribution<float> uniform_dist{0, std::numeric_limits<float>::max()};
//    return uniform_dist(gen);
//}

int main(int argc, char* argv[])
{
    double d{std::stod(argv[2])};

    std::size_t size{std::stoul(argv[1])};
    std::vector<Point> a{size};

    // not necessary, default ctor handles this
    // int i;
    // for (i = 0; i < size; ++i) {
    //     a[i].x = rand_float();
    //     a[i].y = rand_float();
    // }

    int i;
    int cnt{0};
    for (i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (distance(a[i], a[j]) < d) { ++cnt; }
        }
    }
    std::cout << cnt << " pairs within " << d << "\n";
    return 0;
}