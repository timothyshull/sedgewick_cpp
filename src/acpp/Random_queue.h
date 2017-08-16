// Program 18.11 - Random queue implementation
#ifndef RANDOMIZED_GRAPH_SEARCH_H
#define RANDOMIZED_GRAPH_SEARCH_H

#include <vector>
#include <random>

template<typename Item_t>
class Random_queue {
public:
    Random_queue(std::size_t size) : _coll(size + 1), _size(0) {}

    inline int empty() const noexcept { return _size == 0; }

    inline void put(Item_t&& item) { _coll[_size++] = std::forward<Item_t>(item); }

    void update(Item_t&& x) {}

    Item_t get()
    {
        static std::random_device rd;
        static std::default_random_engine gen{rd()};
        std::uniform_int_distribution<> dis{0, _size};
        auto i = dis(gen);
        Item_t t = _coll[i];
        _coll[i] = _coll[_size - 1];
        _coll[_size - 1] = t;
        return _coll[--_size];
    }

private:
    std::vector<Item_t> _coll;
    int _size;
};

#endif // RANDOMIZED_GRAPH_SEARCH_H
