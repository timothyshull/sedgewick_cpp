#ifndef CH_7_3_STACK_SIZE_STACK_H
#define CH_7_3_STACK_SIZE_STACK_H

template<typename T>
class Stack {
public:
    explicit Stack(int);

    void push(T &);

    bool empty();

    T &pop();


};

#endif //CH_7_3_STACK_SIZE_STACK_H
