#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>

struct Segment_tree_node {
    int sum;
    int min;
    int pendignVal;
    int from;
    int to;

    int size();
};

class Segment_tree {
public:
    Segment_tree(std::vector<int>& array);

    int size();

    int rsq(int from, int to);

    int rMinQ(int from, int to);

    void update(int from, int to, int value);

private:
    std::vector<Segment_tree_node> heap;
    std::vector<int> array;
    int size;

    int rsq(int v, int from, int to);

    void build(int v, int from, int size);

    int rMinQ(int v, int from, int to);

    void update(int v, int from, int to, int value);

    void propagate(int v);

    void change(Segment_tree_node* n, int value);

    bool contains(int from1, int to1, int from2, int to2);

    bool intersects(int from1, int to1, int from2, int to2);
};

#endif // SEGMENT_TREE_H
