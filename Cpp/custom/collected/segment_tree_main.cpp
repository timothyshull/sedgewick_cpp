#include "Segment_tree.h"
#include "Std_in.h"
#include "utility.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Segment_tree st;

    std::string cmd{"cmp"};
    while (true) {
        std::string line{Std_in::read_line()};
        std::vector<std::string> lines;
        utility::split_string(line, ' ', lines);

        if (lines[0] == "exit") { break; }

        int arg1{0};
        int arg2{0};
        int arg3{0};

        if (lines.size() > 1) {
            arg1 = utility::str_to_num(lines[1].c_str());
        }
        if (lines.size() > 2) {
            arg2 = utility::str_to_num(lines[2].c_str());
        }
        if (lines.size() > 3) {
            arg3 = utility::str_to_num(lines[3].c_str());
        }

        // TODO: this may not work as expected
        if ((lines[0] != "set" && lines[0] != "init") && st.size() == 0) {
            Std_out::print_line("Segment Tree not initialized");
            continue;
        }
        std::vector<int> vector;
        if (lines[0] == "set") {
            vector.reserve(lines.size() - 1);
            for (int i{0}; i < lines.size() - 1; ++i) {
                vector[i] = utility::str_to_num(lines[i + 1].c_str());
            }
            st = Segment_tree{vector};
        } else if (lines[0] == "init") {
            vector.reserve(static_cast<std::vector<int>::size_type>(arg1));
            std::fill(vector.begin(), vector.end(), arg2);
            st = Segment_tree{vector};

            for (int i{0}; i < st.size(); ++i) {
                Std_out::print(st.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (lines[0] == "up") {
            st.update(arg1, arg2, arg3);
            for (int i{0}; i < st.size(); ++i) {
                Std_out::print(st.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (lines[0] == "rsq") {
            Std_out::printf("Sum from %d to %d = %d size", arg1, arg2, st.rsq(arg1, arg2));
        } else if (lines[0] == "rmq") {
            Std_out::printf("Min from %d to %d = %d size", arg1, arg2, st.r_min_q(arg1, arg2));
        } else {
            Std_out::print_line("Invalid command");
        }

    }

    Std_out::close();
    return 0;
}