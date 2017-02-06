#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

class Union_find {
public:
    explicit Union_find(int n);

    inline int count() const { return _count; }

    int find(int p); // not a const operation

    bool connected(int p, int q); // calls find so not const

    void create_union(int p, int q); // union is a C++ keyword
private:
    std::vector<int> _parent;
    std::vector<short> _rank;
    int _count;

    void _validate(int p) const;
};

#endif // UNION_FIND_H
