#include "Segment_tree.h"
#include "Std_in.h"
#include "utility.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Segment_tree st;

    std::string cmd{"cmp"};
    while (true) {
        std::vector<std::string> line = Std_in::read_line().split(" ");

        if (line[0] == "exit") { break; }

        int arg1{0};
        int arg2{0};
        int arg3{0};

        if (line.size() > 1) {
            arg1 = utility::str_to_num(line[1]);
        }
        if (line.size() > 2) {
            arg2 = utility::str_to_num(line[2]);
        }
        if (line.size() > 3) {
            arg3 = utility::str_to_num(line[3]);
        }

        // TODO: this may not work as expected
        if ((line[0] != "set" && line[0] != "init") && st.size() == 0) {
            Std_out::print_line("Segment Tree not initialized");
            continue;
        }
        std::vector<int> vector;
        if (line[0] == "set") {
            vector.reserve(line.size() - 1);
            for (int i{0}; i < line.size() - 1; ++i) {
                vector[i] = utility::str_to_num(line[i + 1]);
            }
            st = Segment_tree{vector};
        } else if (line[0] == "init") {
            vector.reserve(arg1);
            std::fill(vector.begin(), vector.end(), arg2);
            st = Segment_tree{vector};

            for (int i{0}; i < st.size(); ++i) {
                Std_out::print(st.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0] == "up") {
            st.update(arg1, arg2, arg3);
            for (int i{0}; i < st.size(); ++i) {
                Std_out::print(st.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0] == "rsq") {
            Std_out::printf("Sum from %d to %d = %d size", arg1, arg2, st.rsq(arg1, arg2));
        } else if (line[0] == "rmq") {
            Std_out::printf("Min from %d to %d = %d size", arg1, arg2, st.rMinQ(arg1, arg2));
        } else {
            Std_out::print_line("Invalid command");
        }

    }

    Std_out::close();
    return 0;
}