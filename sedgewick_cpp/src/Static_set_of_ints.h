#ifndef STATIC_Set_OF_INTS_H
#define STATIC_Set_OF_INTS_H

#include <vector>

class Static_set_of_ints {
public:
    Static_set_of_ints() = default;

    Static_set_of_ints(const Static_set_of_ints) = default;

    Static_set_of_ints(Static_set_of_ints&&) = default;

    ~Static_set_of_ints() = default;

    Static_set_of_ints& operator=(const Static_set_of_ints&) = default;

    Static_set_of_ints& operator=(Static_set_of_ints&&) = default;

    Static_set_of_ints(std::vector<int>& keys);

    inline bool contains(int key) const { return rank(key) != -1; };

    int rank(int key);

private:
    std::vector<int> _set;
};

#endif // STATIC_Set_OF_INTS_H
