#include <string>
#include "Max_pq.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Max_pq<std::string> pq{};
    std::string item;
    while (!Std_in::is_empty()) {
        item = Std_in::read_string();
        if (item != "-") {
            pq.insert(item);
        } else if (!pq.is_empty()) {
            Std_out::print_line(pq.delete_max() + " ");
        }
    }
    std::stringstream ss;
    ss << "(" << pq.size() << " left of pq)";
    Std_out::print_line(ss.str());
    return 0;
}