#include <string>
#include "Linked_stack.h"
#include "Std_out.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    Linked_stack<std::string> stack{};
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        if (item != "-") {
            stack.push(item);
        } else if (!stack.is_empty()) {
            Std_out.print(stack.pop() + " ");
        }
    }
    Std_out::print_line("(" + stack.size() + " left on stack)");
    return 0;
}