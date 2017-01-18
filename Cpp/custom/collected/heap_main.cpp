#include "Heap.h"
#include "Std_in.h"
#include "Std_out.h"
#include "utility.h"

int main()
{
    std::vector<std::string> a = Std_in::read_all_strings();
    Heap::sort(a);
    Std_out::print(Heap::to_string(a));
    utility::assert(Heap::is_sorted(a), "The Heap.is_sorted check failed");
    return 0;
}
