// Program 3.20 - A two-dimensional array of lists
#ifndef CLOSEST_POINT_GRID_H
#define CLOSEST_POINT_GRID_H

#include <vector>

#include "Point.h"

struct Node;

using Raw_node_pointer = Node*;

struct Grid {
    std::size_t grid_dimension;
    int count;
    float distance;
    std::vector<std::vector<Raw_node_pointer>> grid;
};

struct Node {
    Node(Point& pt, Raw_node_pointer t) : point{pt}, next{t} {}

    Point point;
    Raw_node_pointer next;
};

void init_grid(float distance, std::size_t grid_dimension);

void grid_insert(float x, float y);

float rand_float();

int get_grid_count();

#endif // CLOSEST_POINT_GRID_H
