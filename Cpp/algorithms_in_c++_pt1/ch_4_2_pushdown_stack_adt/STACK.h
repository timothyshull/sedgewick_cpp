#ifndef CH_4_2_PUSHDOWN_STACK_ADT_STACK_H
#define CH_4_2_PUSHDOWN_STACK_ADT_STACK_H

template<class Item>
class STACK {
private:
    // Implementation-dependent code
public:
    STACK(int);

    int empty() const;

    void push(Item item);

    Item pop();
};

#endif //CH_4_2_PUSHDOWN_STACK_ADT_STACK_H
