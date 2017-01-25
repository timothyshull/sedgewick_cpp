#include <string>
#include "Std_in.h"
#include "Std_out.h"
#include "Resizing_array_queue.h"

int main(int argc, char* argv[])
{
    Resizing_array_queue<std::string> queue{};
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        if (item != "-") { queue.enqueue(item); }
        else if (!queue.is_empty()) { Std_out::print(queue.dequeue() + " "); }
    }
    Std_out::print_line("(" + queue.size() + " left on queue)");
    return 0;
}