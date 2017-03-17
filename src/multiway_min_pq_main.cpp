#include "Multiway_min_pq.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Multiway_min_pq<std::string> pq;
    std::string item;
    while (!Std_in::is_empty()) {
        item = Std_in::read_string();
        if (item != "-") {
            pq.insert(item);
        } else if (!pq.is_empty()) {
            Std_out::print_line(pq.delete_min() + " ");
        }
    }
    std::stringstream ss;
    ss << "(" << pq.size() << " left on _priority_queue)";
    Std_out::print_line(ss.str());
    return 0;
}