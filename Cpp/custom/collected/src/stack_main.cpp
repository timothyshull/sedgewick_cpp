#include "Stack.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Stack<std::string> stack;
    std::string item;
    while (!Std_in::is_empty()) {
        item = Std_in::read_string();
        if (item != "-") {
            stack.push(item);
        } else if (!stack.is_empty()) {
            Std_out::print(stack.pop() + " ");
        }
    }
    Std_out::print_line("(" + std::to_string(stack.size()) + " left on stack)");
    return 0;
}