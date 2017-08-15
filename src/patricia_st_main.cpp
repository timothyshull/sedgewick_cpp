#include <sstream>
#include "Patricia_st.h"
#include "Std_out.h"
#include "utility.h"
#include "Std_random.h"

int main(int argc, char* argv[])
{
    Patricia_st<int> st{};
    auto limit_item = 1000000;
    auto limit_pass = 1;
    auto count_pass = 0;
    bool ok{true};

    if (argc > 0) { limit_item = utility::str_to_num(argv[1]); }
    if (argc > 1) { limit_pass = utility::str_to_num(argv[2]); }

    do {
        std::vector<std::string> a;
        a.reserve(limit_item);
        std::vector<int> v;
        v.reserve(limit_item);

        Std_out::printf("Creating dataset (%d items)...\n", limit_item);
        std::stringstream ss;
        for (auto i = 0; i < limit_item; ++i) {
            ss.str("");
            ss << std::showbase << std::hex << i;
            a[i] = ss.str();
            v[i] = i;
        }

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(v);

        Std_out::printf("Adding (%d items)...\n", limit_item);
        for (auto i = 0; i < limit_item; ++i) {
            st.put(a[v[i]], v[i]);
        }

        auto count_keys = 0;
        Std_out::printf("Iterating...\n");
        for (auto key : st.keys()) { ++count_keys; }
        Std_out::printf("%d items iterated\n", count_keys);
        if (count_keys != limit_item) { ok = false; }
        if (count_keys != st.size()) { ok = false; }

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(v);

        auto limit_delete = limit_item / 2;
        Std_out::printf("Deleting (%d items)...\n", limit_delete);
        for (auto i = 0; i < limit_delete; ++i) {
            st.remove(a[v[i]]);
        }

        count_keys = 0;
        Std_out::printf("Iterating...\n");
        for (auto key : st.keys()) { ++count_keys; }
        Std_out::printf("%d items iterated\n", count_keys);
        if (count_keys != limit_item - limit_delete) { ok = false; }
        if (count_keys != st.size()) { ok = false; }

        auto count_delete = 0;
        auto count_remain = 0;
        Std_out::printf("Checking...\n");
        for (auto i = 0; i < limit_item; ++i) {
            if (i < limit_delete) {
                if (!st.contains(a[v[i]])) { ++count_delete; }
            } else {
                int val = st.get(a[v[i]]);
                if (val == v[i]) { ++count_remain; }
            }
        }
        Std_out::printf("%d items found and %d (deleted) items missing\n",
                        count_remain, count_delete);
        if (count_remain + count_delete != limit_item) { ok = false; }
        if (count_remain != st.size()) { ok = false; }
        if (st.is_empty()) { ok = false; }

        Std_out::printf("Deleting the rest (%d items)...\n", limit_item - count_delete);
        for (auto i = count_delete; i < limit_item; ++i) {
            st.remove(a[v[i]]);
        }
        if (!st.is_empty()) { ok = false; }

        ++count_pass;
        if (ok) { Std_out::printf("PASS %d TESTS SUCCEEDED\n", count_pass); }
        else { Std_out::printf("PASS %d TESTS FAILED\n", count_pass); }
    } while (ok && count_pass < limit_pass);

    if (!ok) { throw utility::Runtime_exception{"TESTS FAILED"}; }
    return 0;
}