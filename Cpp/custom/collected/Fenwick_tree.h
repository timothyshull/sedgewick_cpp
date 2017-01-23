

#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>

class Fenwick_tree {
public:
    Fenwick_tree(int size);
    int rsq(int ind);
    int rsq(int a, int b);
    void update(int ind, int value);
    int size();
private:
    std::vector<int> array;
};

#endif // FENWICK_TREE_H
