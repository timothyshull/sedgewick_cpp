#ifndef PATRICIA_SET_H
#define PATRICIA_SET_H

#include <string>
#include "Queue.h"

struct Patricia_set_node;

struct Patricia_set_node {
    using Raw_node_pointer = Patricia_set_node*;

    Raw_node_pointer left;
    Raw_node_pointer right;
    std::string key;
    int b;

    Patricia_set_node(std::string& key, int b);
};

class Patricia_set {
public:
    using Raw_node_pointer = Patricia_set_node*;

    Patricia_set();

    void add(std::string& key);

    bool contains(std::string& key);

    void remove(std::string& key);

    bool isEmpty();

    int size();

    std::string toString();

private:
    Raw_node_pointer head;
    int count;

    void collect(Raw_node_pointer x, int b, Queue<std::string> queue);

    bool safeBitTest(std::string& key, int b);

    int bitTest(std::string& key, int b);

    int safeCharAt(std::string& key, int i);

    int firstDifferingBit(std::string& k1, std::string& k2);
};

#endif // PATRICIA_SET_H
