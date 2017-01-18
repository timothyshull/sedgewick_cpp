#ifndef COUNTER_H
#define COUNTER_H

#include <string>
#include <sstream>

class Counter {
private:
    std::string _name;
    int _count;

public:
    explicit Counter(std::string id) : _name{id}, _count{0} {}

    Counter() : _name{""}, _count{0} {}

    void increment() { ++_count; }

    inline int tally() const { return _count; }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Counter(count: " << _count << ", name: " << _name << ")";
        return ss.str();
    }

    int compare_to(Counter& that) const
    {
        if (this->_count < that._count) {
            return -1;
        } else if (this->_count > that._count) {
            return 1;
        }
        return 0;
    }
};

std::ostream& operator<<(std::ostream& os, const Counter& out)
{
    return os << out.to_string();
}

#endif // COUNTER_H
