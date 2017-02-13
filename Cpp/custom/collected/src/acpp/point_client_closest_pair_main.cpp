// Program 4.2 - Point client (closest-point computation)
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Point.h"

int main(int argc, char* argv[])
{
    std::size_t size{std::stoul(argv[1])};
    std::vector<Point> coll(size, Point{});

    double distance{std::stod(argv[2])};
    int count{0};

    for (int i{0}; i < size; ++i) {
        for (int j{i + 1}; j < size; ++j) {
            if (coll[i].distance(coll[j]) < distance) { ++count; }
        }
    }
    std::cout << count << " pairs within " << distance << "\n";
    return 0;
}
