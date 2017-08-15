// Program 4.6 - Infix-to-postfix conversion
#include <iostream>
#include "Linked_list_stack.h"

int main(int argc, char* argv[])
{
    std::string str{argv[1]};
    auto size = str.size();
    // Stack<char> ops{size};
    Stack<char> ops;
    for (auto i = 0; i < size; i++) {
        if (str[i] == ')') {
            std::cout << ops.pop() << " ";
        }
        if ((str[i] == '+') || (str[i] == '*')) {
            ops.push(str[i]);
        }
        if ((str[i] >= '0') && (str[i] <= '9')) {
            std::cout << str[i] << " ";
        }
    }
    std::cout << "\n";
    return 0;
}
