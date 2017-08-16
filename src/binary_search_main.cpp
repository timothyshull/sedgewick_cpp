#include "Binary_search.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    auto whitelist = Std_in::read_all_ints();
    std::sort(whitelist.begin(), whitelist.end());
    auto to_check = Std_in::read_all_ints();

    for (auto key : to_check) {
        if (Binary_search::index_of(whitelist, key) == -1) {
            Std_out::printf("The key %d is not in the whitelisted values", key);
        } else {
            Std_out::printf("The key %d is in the whitelisted values", key);
        }
    }

    return 0;
}