#include <string>
#include "In.h"
#include "Queue.h"
#include "Symbol_table.h"
#include "Std_out.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    std::string filename{argv[1]};
    char separator{*argv[2]};
    In in{filename};

    Symbol_table<std::string, Queue<std::string>> st;
    Symbol_table<std::string, Queue<std::string>> ts;

    while (in.has_next_line()) {
        std::string line{in.read_line()};
        std::vector<std::string> fields;
        utility::split_string(line, separator, fields);
        std::string key{fields[0]};
        std::string val;
        for (int i{1}; i < fields.size(); ++i) {
            val = fields[i];
            if (!st.contains(key)) { st.put(key, Queue<std::string>()); }
            if (!ts.contains(val)) { ts.put(val, Queue<std::string>()); }
            st.get(key).enqueue(val);
            ts.get(val).enqueue(key);
        }
    }

    Std_out::print_line("Done indexing");

    std::string query;
    while (!Std_in::is_empty()) {
        query = Std_in::read_line();
        if (st.contains(query)) {
            for (auto vals : st.get(query)) {
                Std_out::print_line("  " + vals);
            }
        }
        if (ts.contains(query)) {
            for (auto keys : ts.get(query)) {
                Std_out::print_line("  " + keys);
            }
        }
    }
    return 0;
}