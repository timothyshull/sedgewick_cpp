#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>

template<typename Key, typename Value>
class Symbol_table {
public:

ST() {
        st = new TreeMap<Key, Value>();
    }


Value get(Key key) {
        if (key == null) throw new NullPointerException("called get() with null key");
        return st.get(key);
    }

void put(Key key, Value val) {
        if (key == null) throw new NullPointerException("called put() with null key");
        if (val == null) st.remove(key);
        else st.put(key, val);
    }

void remove(Key key) {
        if (key == null) throw new NullPointerException("called delete() with null key");
        st.remove(key);
    }
 bool contains(Key key) {
        if (key == null) throw new NullPointerException("called contains() with null key");
        return st.containsKey(key);
    }

int size() {
        return st.size();
    }
 bool is_empty() {
        return size() == 0;
    }

Iterable<Key> keys() {
        return st.keySet();
    }

Iterator<Key> iterator() {
        return st.keySet().iterator();
    }

Key min() {
        if (is_empty()) throw new NoSuchElementException("called min() with empty symbol table");
        return st.firstKey();
    }

Key max() {
        if (is_empty()) throw new NoSuchElementException("called max() with empty symbol table");
        return st.lastKey();
    }

Key ceiling(Key key) {
        if (key == null) throw new NullPointerException("called ceiling() with null key");
        Key k = st.ceilingKey(key);
        if (k == null) throw new NoSuchElementException("all keys are less than " + key);
        return k;
    }

Key floor(Key key) {
        if (key == null) throw new NullPointerException("called floor() with null key");
        Key k = st.floorKey(key);
        if (k == null) throw new NoSuchElementException("all keys are greater than " + key);
        return k;
    }

private:
    std::map<Key, Value> st;
};

#endif // SYMBOL_TABLE_H
