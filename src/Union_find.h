#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

class Union_find {
private:
    std::vector<int> _parent;
    std::vector<short> _rank;
    int _count;

public:
    explicit Union_find(int n);

    inline int count() const { return _count; }

    int find(int p); // not a const operation

    inline bool connected(int p, int q) { return find(p) == find(q); }

    void create_union(int p, int q); // union is a C++ keyword

private:
    void _validate(int p) const;

};

#endif // UNION_FIND_H
