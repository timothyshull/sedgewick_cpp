#include "Stack.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Stack<std::string> stack;

    std::vector<std::string> v = Std_in::read_all_strings();

    for (auto s : v) {
        if (s != "-") {
            stack.push(s);
        } else if (!stack.is_empty()) {
            Std_out::print(stack.pop() + " ");
        }
    }
    Std_out::printf("(%d left on stack)", stack.size());
    return 0;
}