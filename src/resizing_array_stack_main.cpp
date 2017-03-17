#include <string>
#include "Std_in.h"
#include "Std_out.h"
#include "Resizing_array_stack.h"

int main(int argc, char* argv[])
{
    Resizing_array_stack<std::string> stack;
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        if (item != "-") { stack.push(item); }
        else if (!stack.is_empty()) { Std_out::print(stack.pop() + " "); }
    }
    Std_out::print_line("(" + std::to_string(stack.size()) + " left on stack)");
    return 0;
}