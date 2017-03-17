// Program 4.5 - Postfix-expression evaluation
#include <iostream>
#include "Linked_list_stack.h"

int main(int argc, char* argv[])
{
    std::string str{argv[1]};
    auto size = str.size();
    // Stack<int> save{size};
    Stack<int> save;
    for (int i{0}; i < size; ++i) {
        if (str[i] == '+') {
            save.push(save.pop() + save.pop());
        }
        if (str[i] == '*') {
            save.push(save.pop() * save.pop());
        }
        if ((str[i] >= '0') && (str[i] <= '9')) {
            save.push(0);
        }
        while ((str[i] >= '0') && (str[i] <= '9')) {
            save.push(10 * save.pop() + (str[i++] - '0'));
        }
    }
    std::cout << save.pop() << "\n";
    return 0;
}

