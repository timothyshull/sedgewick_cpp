#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <vector>
#include "utility.h"

template<typename Key, typename Value>
class Symbol_table {
public:
    using Key_type = Key;
    using Value_type = Value;
    using Key_iterator_type = typename std::vector<Key_type>::iterator;
    using Iterator_type = typename std::map<Key_type, Value_type>::iterator;

    Symbol_table() = default;

    Symbol_table(const Symbol_table&) = default;

    Symbol_table(Symbol_table&&) = default;

    ~Symbol_table() = default;

    Symbol_table& operator=(const Symbol_table&) = default;

    Symbol_table& operator=(Symbol_table&&) = default;

    inline Value_type get(Key_type& key) { return _st.get(key); }

    inline Value_type get(Key_type&& key) { return _st.get(key); }

    inline void put(Key_type& key, Value_type& val) { _st.put(key, val); }

    inline void put(Key_type&& key, Value_type&& val) { _st.put(key, val); }

    inline void remove(Key_type& key) { _st.remove(key); }

    inline void remove(Key_type&& key) { _st.remove(key); }

    inline bool contains(Key_type& key) const { return _st.find(key) != _st.end(); }

    inline bool contains(Key_type&& key) const { return _st.find(key) != _st.end(); }

    inline std::size_t size() const noexcept { return _st.size(); }

    inline bool is_empty() const noexcept { return size() == 0; }

    std::vector<Key_type> keys()
    {
        std::vector<Key_type> tmp{_st.size()};
        for (auto p : _st) {
            tmp.emplace_back(p.first);
        }
        return tmp;
    }

    // TODO: this isn't a good pattern
    Key_iterator_type key_iterator_begin() { return keys().begin(); }

    Key_iterator_type key_iterator_end() { return keys().end(); }

    Iterator_type begin() { return _st.begin(); }

    Iterator_type end() { return _st.end(); }

    Key_type min()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"called min() with empty symbol table"}; }
        return (*_st.begin()).first;
    }

    Key_type max()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"called max() with empty symbol table"}; }
        auto it = _st.end();
        --it;
        return (*it).first;
    }

    Key_type ceiling(Key_type& key)
    {
        auto it = _st.upper_bound(key);
        if (k == null) { throw utility::No_such_element_exception{"all keys are less than " + key}; }
        return *it;
    }

    Key_type floor(Key_type& key)
    {
        auto it = _st.lower_bound(key);
        if (k == null) { throw utility::No_such_element_exception{"all keys are greater than " + key}; }
        return *it;
    }

private:
    std::map<Key, Value> _st;
};

#endif // SYMBOL_TABLE_H
