#ifndef LINEAR_PROBING_HASH_SYMBOL_TABLE_H
#define LINEAR_PROBING_HASH_SYMBOL_TABLE_H

#include <vector>
#include <sstream>
#include <iostream>
#include "utility.h"

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class Linear_probing_hash_symbol_table {
public:
    using Key_type = Key;
    using Value_type = Value;

    Linear_probing_hash_symbol_table() : Linear_probing_hash_symbol_table{_initial_capacity} {}

    Linear_probing_hash_symbol_table(int capacity)
            : _table_size{capacity},
              _num_kv_pairs{0},
              _keys(static_cast<typename std::vector<Key_type>::size_type>(capacity)),
              _values(static_cast<typename std::vector<Value_type>::size_type>(capacity)) {}

    inline int size() const { return _num_kv_pairs; }

    inline int is_empty() const { return _num_kv_pairs == 0; }

    bool contains(Key_type& key)
    {
        return get(key) != nullptr;
    }

    void resize(int capacity)
    {
        Linear_probing_hash_symbol_table<Key_type, Value_type> temp{capacity};
        for (auto i = 0; i < _table_size; ++i) {
            if (_keys[i] != nullptr) {
                temp.put(*_keys[i], *_values[i]);
            }
        }
        *this = temp;
    }

    void put(Key_type& key, Value_type& value)
    {
        if (_num_kv_pairs >= _table_size / 2) {
            resize(2 * _table_size);
        }

        int i;
        for (i = _hash(key); _keys[i] != nullptr; i = (i + 1) % _table_size) {
            if (*_keys[i] == key) {
                _values[i] = new Value{value};
                return;
            }
        }
        _keys[i] = new Key{key};
        _values[i] = new Value{value};
        ++_num_kv_pairs;
    }

    Value_type* get(Key_type& key)
    {
        for (auto i = _hash(key); _keys[i] != nullptr; i = (i + 1) % _table_size) {
            if (*_keys[i] == key) {
                return _values[i];
            }
        }
        return nullptr;
    }

    void remove(Key_type& key)
    {
        if (!contains(key)) {
            return;
        }

        int i = _hash(key);
        while (key != *_keys[i]) {
            i = (i + 1) % _table_size;
        }

        delete _keys[i];
        _keys[i] = nullptr;
        delete _values[i];
        _values[i] = nullptr;

        i = (i + 1) % _table_size;
        while (_keys[i] != nullptr) {
            Key_type key_to_rehash = *_keys[i];
            Value val_to_rehash = *_values[i];
            delete _keys[i];
            _keys[i] = nullptr;
            delete _values[i];
            _values[i] = nullptr;
            --_num_kv_pairs;
            put(key_to_rehash, val_to_rehash);
            i = (i + 1) % _table_size;
        }
        --_num_kv_pairs;

        if (_num_kv_pairs > 0 && _num_kv_pairs <= _table_size / 8) {
            resize(_table_size / 2);
        }

        utility::alg_assert(_check(), "The Linear_probing_hash_symbol_table invariant _check failed after delete()");
    }

    std::vector<Key_type> keys() {
        std::vector<Key_type> kv;
        for (auto p : _keys) {
            if (p != nullptr) {
                kv.emplace_back(*p);
            }
        }
        return kv;
    }

private:
    int _num_kv_pairs;
    int _table_size;
    std::vector<Key_type*> _keys;
    std::vector<Value_type*> _values;
    const static int _initial_capacity = 4;

    int _hash(Key_type& key)
    {
        return (Hash{}(key) & 0x7fffffff) % _table_size;
    }

    bool _check()
    {
        if (_table_size < 2 * _num_kv_pairs) {
            std::cerr << "Hash table size m = " << _table_size << "; vector size _size = " << _num_kv_pairs << "\n";
            return false;
        }

        for (auto i = 0; i < _table_size; ++i) {
            if (_keys[i] == nullptr) {
                continue;
            } else if (*get(*_keys[i]) != *_values[i]) {
                std::cerr << "get[" << *_keys[i] << "] = " << *get(_keys[i]) << "; _values[i] = " << *_values[i] << "\n";
                return false;
            }
        }
        return true;
    }
};

#endif // LINEAR_PROBING_HASH_SYMBOL_TABLE_H
