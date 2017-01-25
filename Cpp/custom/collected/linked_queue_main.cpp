#include <string>
#include "Linked_queue.h"
#include "Std_out.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    Linked_queue<std::string> queue{};
    while (!Std_in.is_empty()) {
        std::string item{Std_in.read_string()};
        if (item != "-") {
            queue.enqueue(item);
        } else if (!queue.is_empty()) {
            Std_out.print(queue.dequeue() + " ");
        }
    }
    Std_out.println("(" + queue.size() + " left on queue)");
    return 0;
}