#ifndef PATRICIA_Set_H
#define PATRICIA_Set_H

#include <string>
#include "Queue.h"

class Patricia_set_node;

class Patricia_set;

class Patricia_set_node {
public:
    using Raw_node_pointer = Patricia_set_node*;

    Patricia_set_node(std::string& key, int b);

    Patricia_set_node(std::string&& key, int b);

private:
    Raw_node_pointer left;
    Raw_node_pointer right;
    std::string key;
    int b;

    friend class Patricia_set;
};

class Patricia_set {
public:
    using Raw_node_pointer = Patricia_set_node*;

    Patricia_set();

    void add(std::string& key);

    bool contains(std::string& key);

    void remove(std::string& key);

    bool is_empty();

    int size();

    std::string to_string();

private:
    Raw_node_pointer head;
    int count;

    void _collect(Raw_node_pointer x, int b, Queue<std::string> queue);

    bool _safe_bit_test(std::string& key, int b);

    int _bit_test(std::string& key, int b);

    int _safe_char_at(std::string& key, int i);

    int _first_differing_bit(std::string& k1, std::string& k2);
};

#endif // PATRICIA_Set_H
