// Program 18.11 - Random queue implementation
#ifndef RANDOMIZED_GRAPH_SEARCH_H
#define RANDOMIZED_GRAPH_SEARCH_H

#include <vector>
#include <random>

template<typename Item_type>
class Random_queue {
public:
    Random_queue(std::size_t size) : _coll(size + 1), _size(0) {}

    inline int empty() const noexcept { return _size == 0; }

    inline void put(Item_type&& item) { _coll[_size++] = std::forward<Item_type>(item); }

    void update(Item_type&& x) {}

    Item_type get()
    {
        static std::random_device rd;
        static std::default_random_engine gen{rd()};
        std::uniform_int_distribution<> dis{0, _size};
        int i{dis(gen)};
        Item_type t = _coll[i];
        _coll[i] = _coll[_size - 1];
        _coll[_size - 1] = t;
        return _coll[--_size];
    }

private:
    std::vector<Item_type> _coll;
    int _size;
};

#endif // RANDOMIZED_GRAPH_SEARCH_H
