#include "Binary_search.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<int> whitelist = Std_in::read_all_ints();

    std::sort(whitelist.begin(), whitelist.end());

    std::vector<int> to_check = Std_in::read_all_ints();

    for (auto key : to_check) {
        if (Binary_search::index_of(whitelist, key) == -1) {
            Std_out::printf("The key %d is not _in the whitelisted values", key);
        } else {
            Std_out::printf("The key %d is _in the whitelisted values", key);
        }
    }

    return 0;
}