#include "Fenwick_tree.h"
#include "utility.h"

Fenwick_tree::Fenwick_tree(int size) : _vector(static_cast<std::vector<int>::size_type>(size)) {}

int Fenwick_tree::rsq(int index)
{
    utility::alg_assert(index > 0, "Fenwick_tree range sum query must be passed an index greater than 0");
    int sum = 0;
    while (index > 0) {
        sum += _vector[index];
        index -= index & (-index);
    }

    return sum;
}

int Fenwick_tree::rsq(int a, int b)
{
    utility::alg_assert(b >= a && a > 0 && b > 0, "Fenwick_tree range sum query index value check failed");
    return rsq(b) - rsq(a - 1);
}

void Fenwick_tree::update(int index, int value)
{
    utility::alg_assert(index > 0, "Fenwick_tree range sum query must be passed an index greater than 0");
    while (index < _vector.size()) {
        _vector[index] += value;
        index += index & (-index);
    }
}


