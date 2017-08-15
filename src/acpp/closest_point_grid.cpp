// Program 3.20 - A two-dimensional array of lists
#include <random>
#include "closest_point_grid.h"

static Grid global_grid;

void init_grid(float distance, std::size_t grid_dimension)
{
    global_grid.count = 0;
    global_grid.distance = distance;
    global_grid.grid_dimension = grid_dimension;
    global_grid.grid.reserve(grid_dimension + 2);
    for (auto i = 0; i < grid_dimension + 2; ++i) {
        for (auto j = 0; j < grid_dimension + 2; ++j) {
            global_grid.grid[i][j] = nullptr;
        }
    }
}

void grid_insert(float x, float y)
{
    auto x2 = static_cast<int>(x * global_grid.grid_dimension) + 1;
    auto y2 = static_cast<int>(y * global_grid.grid_dimension) + 1;
    Point p;
    p.x = x;
    p.y = y;
    Raw_node_pointer s;
    Raw_node_pointer t = new Node{p, global_grid.grid[x][y]};
    for (int i = x2 - 1; i <= x2 + 1; ++i) {
        for (int j = y2 - 1; j <= y2 + 1; ++j) {
            for (s = global_grid.grid[i][j]; s != nullptr; s = s->next) {
                if (distance(s->point, t->point) < global_grid.distance) { ++global_grid.count; }
            }
        }
    }
    global_grid.grid[x2][y2] = t;
}

float rand_float()
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<float> uniform_dist{0, std::numeric_limits<float>::max()};
    return uniform_dist(gen);
}

int get_grid_count() { return global_grid.count; }
