#ifndef MULTIWAY_MIN_PQ_H
#define MULTIWAY_MIN_PQ_H

#include <vector>

#include "utility.h"

template<typename Key, typename Comparator = std::less<Key>>
class Multiway_min_pq {
public:
    Multiway_min_pq(int dimension)
            : _dimension{dimension},
              _order{1},
              _keys(static_cast<std::vector<Key>::size_type>(dimension << 1)),
              _comp{}
    {
        if (dimension < 2) { throw utility::Illegal_argument_exception{"Dimension should be 2 or over"}; }
    }

    Multiway_min_pq(std::vector<Key>& a, int dimension)
            : _dimension{dimension},
              _order{1},
              _keys{a},
              _comp{}
    {
        if (dimension < 2) { throw utility::Illegal_argument_exception{"Dimension should be 2 or over"}; }
    }

    bool is_empty() { return _size == 0; };

    int size() { return _size; }

    void insert(Key& key)
    {
        _keys[_size + _dimension] = key;
        swim(_size++);
        if (_size == _keys.size() - _dimension) {
            resize(getN(_order + 1) + _dimension);
            ++_order;
        }
    }

    Key min_key()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        return _keys[_dimension];
    }

    Key delete_min()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        exch(0, --_size);
        sink(0);
        Key min = _keys[_size + _dimension];
        _keys[_size + _dimension] = nullptr;
        int number = getN(_order - 2);
        if (_order > 1 && _size == number) {
            resize(number + (int) std::pow(_dimension, _order - 1) + _dimension);
            _order--;
        }
        return min;
    }

private:
    const int _dimension;
    int _size;
    int _order;
    std::vector<Key> _keys;
    const Comparator _comp;

    bool greater(int x, int y)
    {
        int i = x + _dimension, j = y + _dimension;
        if (_keys[i] == nullptr) { return false; }
        if (_keys[j] == nullptr) { return true; }
        return _comp.compare(_keys[i], _keys[j]) > 0;
    }

    void exch(int x, int y)
    {
        int i = x + _dimension, j = y + _dimension;
        Key swap = _keys[i];
        _keys[i] = _keys[j];
        _keys[j] = swap;
    }

    int getN(int order)
    {
        return (1 - ((int) std::pow(_dimension, order + 1))) / (1 - _dimension);
    }

    void swim(int i)
    {
        if (i > 0 && greater((i - 1) / _dimension, i)) {
            exch(i, (i - 1) / _dimension);
            swim((i - 1) / _dimension);
        }
    }

    void sink(int i)
    {
        int child = _dimension * i + 1;
        if (child >= _size) { return; }
        int min = minChild(i);
        while (min < _size && greater(i, min)) {
            exch(i, min);
            i = min;
            min = minChild(i);
        }
    }

    int minChild(int i)
    {
        int loBound = _dimension * i + 1, hiBound = _dimension * i + _dimension;
        int min = loBound;
        for (auto cur = loBound; cur <= hiBound; ++cur) {
            if (cur < _size && greater(min, cur)) { min = cur; }
        }
        return min;
    }

    void resize(int size)
    {
        std::vector<Key> array;
        array.reserve(size);
        for (auto i = 0; i < std::min(_keys.size(), array.size()); ++i) {
            array[i] = _keys[i];
            _keys[i] = nullptr;
        }
        _keys = array;
    }

};

#endif // MULTIWAY_MIN_PQ_H
