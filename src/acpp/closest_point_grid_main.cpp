// Program 3.20 - A two-dimensional array of lists
#include <string>
#include <iostream>
#include "closest_point_grid.h"

int main(int argc, char* argv[])
{
    std::size_t size{std::stoul(argv[1])};
    float distance{std::stof(argv[2])};
    auto grid_dimension = static_cast<int>(1 / distance);
    init_grid(distance, grid_dimension);
    for (auto i = 0; i < size; ++i) {
        grid_insert(rand_float(), rand_float());
    }
    std::cout << get_grid_count() << " pairs within " << distance << "\n";
    return 0;
}