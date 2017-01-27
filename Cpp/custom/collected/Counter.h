#ifndef COUNTER_H
#define COUNTER_H

#include <string>
#include <sstream>

class Counter {
public:
    inline explicit Counter(std::string& id) : _name{id}, _count{0} {}

    inline Counter() : _name{""}, _count{0} {}

    inline void increment() { ++_count; }

    inline int tally() const { return _count; }

    std::string to_string() const;

    bool operator<(Counter& rhs) const;

private:
    std::string _name;
    int _count;
};

std::ostream& operator<<(std::ostream& os, const Counter& out);

#endif // COUNTER_H
