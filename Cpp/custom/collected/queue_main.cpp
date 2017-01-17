#include "Queue.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Queue<std::string> queue;

    std::vector<std::string> v = Std_in::read_all_strings();

    for (auto s : v) {
        if (s != "-") {
            queue.enqueue(s);
        } else if (!queue.is_empty()) {
            Std_out::print(queue.dequeue() + " ");
        }
    }
    Std_out::print_line(queue);
    Std_out::printf("(%d left on queue)", queue.size());
    return 0;
}
