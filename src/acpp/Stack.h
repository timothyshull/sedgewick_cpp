// Program 4.4 - Pushdown-stack ADT interface
#ifndef STACK_H
#define STACK_H

#include <cstddef>

template<typename Item_type>
class Stack {
private:
    // Implementation-dependent code
public:
    explicit Stack(std::size_t);

    bool empty() const;

    void push(Item_type& item);

    void push(Item_type&& item);

    Item_type pop();
};

#endif // STACK_H
