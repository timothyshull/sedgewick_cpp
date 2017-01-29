#include "Queue.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Queue<std::string> queue;
    std::string item;
    while (!Std_in::is_empty()) {
        item = Std_in::read_string();
        if (item != "-") {
            queue.enqueue(item);
        } else if (!queue.is_empty()) {
            Std_out::print(queue.dequeue() + " ");
        }
    }
    Std_out::print_line("(" + std::to_string(queue.size()) + " left on queue)");
    return 0;
}
