#ifndef SEPARATE_CHAINING_HASH_ST_H
#define SEPARATE_CHAINING_HASH_ST_H

#include "Sequential_search_st.h"
#include "utility.h"
#include "Queue.h"

template<typename Key, typename Value>
class Separate_chaining_hash_st {
public:
    using Key_type = Key;
    using Value_type = Value;

    Separate_chaining_hash_st() : Separate_chaining_hash_st{_initial_capacity} {}

    Separate_chaining_hash_st(int m)
            : _table_size{m},
              _st(static_cast<std::vector<Sequential_search_st<Key_type, Value_type>>::size_type>(m))
    {
        for (int i = 0; i < m; i++) {
            _st[i] = Sequential_search_st<Key, Value>{};
        }
    }

    void resize(int chains)
    {
        Separate_chaining_hash_st<Key, Value> temp{chains};
        for (int i = 0; i < _table_size; i++) {
            for (auto key : _st[i].keys()) {
                temp.put(key, _st[i].get(key));
            }
        }
        _table_size = temp._table_size;
        _num_pairs = temp._num_pairs;
        _st = temp._st;
    }

    inline std::size_t hash(Key_type& key) const { return (_hash(key) & 0x7fffffff) % _table_size; }

    inline int size() const noexcept { return _num_pairs; }

    inline bool is_empty() const noexcept { return _num_pairs == 0; }

    bool contains(Key key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"argument to contains() is nullptr"}; }
        return get(key) != nullptr;
    }

    Value get(Key key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"argument to get() is nullptr"}; }
        auto i = hash(key);
        return _st[i].get(key);
    }

    void put(Key key, Value val)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"first argument to put() is nullptr"}; }
        if (val == nullptr) {
            remove(key);
            return;
        }

        if (_num_pairs >= 10 * _table_size) { resize(2 * _table_size); }

        auto i = hash(key);
        if (!_st[i].contains(key)) { ++_num_pairs; }
        _st[i].put(key, val);
    }

    void remove(Key key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"argument to delete() is nullptr"}; }

        auto i = hash(key);
        if (_st[i].contains(key)) { --_num_pairs; }
        _st[i].remove(key);

        if (_table_size > _initial_capacity && _num_pairs <= 2 * _table_size) { resize(_table_size / 2); }
    }

    Queue<Key_type> keys()
    {
        Queue<Key> queue;
        for (int i = 0; i < _table_size; i++) {
            for (Key key : _st[i].keys()) {
                queue.enqueue(key);
            }
        }
        return queue;
    }

private:
    static const int _initial_capacity = 4;
    int _num_pairs;
    int _table_size;
    std::vector<Sequential_search_st<Key_type, Value_type>> _st;
    std::hash<Key_type> _hash = std::hash<Key_type>{};

};

#endif // SEPARATE_CHAINING_HASH_ST_H
