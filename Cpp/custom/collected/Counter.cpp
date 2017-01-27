#include "Counter.h"

std::string Counter::to_string() const
{
    std::stringstream ss;
    ss << "Counter(count: " << _count << ", name: " << _name << ")";
    return ss.str();
}

bool Counter::operator<(Counter& rhs) const
{
    return this->_count < rhs._count;
}

std::ostream& operator<<(std::ostream& os, const Counter& out)
{
    return os << out.to_string();
}
