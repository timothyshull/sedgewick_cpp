#include <vector>
#include "Patricia_set.h"
#include "Std_out.h"
#include "Std_random.h"

int main(int argc, char* argv[])
{
    Patricia_set set{};
    int limit_item{1000000};
    int limit_pass{1};
    int count_pass{0};
    bool ok{true};

    if (argc > 0) { limit_item = utility::str_to_num(argv[1]); }
    if (argc > 1) { limit_pass = utility::str_to_num(argv[2]); }

    do {
        std::vector<std::string> a;
        a.reserve(limit_item);

        Std_out::printf("Creating dataset (%d items)...\n", limit_item);
        std::stringstream ss;
        for (int i = 0; i < limit_item; ++i) {
            ss.str("");
            ss << std::showbase << std::hex << i;
            a[i] = ss.str();
        }

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(a);

        Std_out::printf("Adding (%d items)...\n", limit_item);
        for (int i = 0; i < limit_item; ++i) {
            set.add(a[i]);
        }

        int count_items{0};
        Std_out::printf("Iterating...\n");
        for (auto key : set) { ++count_items; }
        Std_out::printf("%d items iterated\n", count_items);
        if (count_items != limit_item) { ok = false; }
        if (count_items != set.size()) { ok = false; }

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(a);

        int limit_delete{limit_item / 2};
        Std_out::printf("Deleting (%d items)...\n", limit_delete);
        for (int i = 0; i < limit_delete; ++i) {
            set.remove(a[i]);
        }

        count_items = 0;
        Std_out::printf("Iterating...\n");
        for (auto key : set) { ++count_items; }
        Std_out::printf("%d items iterated\n", count_items);
        if (count_items != limit_item - limit_delete) { ok = false; }
        if (count_items != set.size()) { ok = false; }

        int count_delete{0};
        int count_remain{0};
        Std_out::printf("Checking...\n");
        for (int i = 0; i < limit_item; ++i) {
            if (i < limit_delete) {
                if (!set.contains(a[i])) { ++count_delete; }
            } else {
                if (set.contains(a[i])) { ++count_remain; }
            }
        }
        Std_out::printf("%d items found and %d (deleted) items missing\n", count_remain, count_delete);
        if (count_remain + count_delete != limit_item) { ok = false; }
        if (count_remain != set.size()) { ok = false; }
        if (set.is_empty()) { ok = false; }

        Std_out::printf("Deleting the rest (%d items)...\n",
                        limit_item - count_delete);
        for (int i = count_delete; i < limit_item; ++i) {
            set.remove(a[i]);
        }
        if (!set.is_empty()) { ok = false; }

        ++count_pass;
        if (ok) {
            Std_out::printf("PASS %d TESTS SUCCEEDED\n", count_pass);
        } else {
            Std_out::printf("PASS %d TESTS FAILED\n", count_pass);
        }
    } while (ok && count_pass < limit_pass);

    if (!ok) { throw utility::Runtime_exception{"TESTS FAILED"}; }
    return 0;
}