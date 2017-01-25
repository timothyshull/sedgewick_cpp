#include <string>
#include <vector>
#include "Std_in.h"
#include "Std_out.h"
#include "Fenwick_tree.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    Fenwick_tree ft;

    std::string cmd{"cmp"};
    int arg1;
    int arg2;
    while (true) {
        std::vector<std::string> line;
        utility::split_string(Std_in::read_line(), ' ', line);

        if (line[0] == "exit") { break; }

        arg1 = 0;
        arg2 = 0;

        if (line.size() > 1) {
            arg1 = utility::str_to_num(line[1]);
        }
        if (line.size() > 2) {
            arg2 = utility::str_to_num(line[2]);
        }

        // TODO: this might always return false
        if ((line[0] != "set" && line[0] != "init") && ft.size() == 0) {
            Std_out::print_line("Fenwick_tree not initialized");
            continue;
        }

        if (line[0] == "init") {
            ft = Fenwick_tree{arg1};
            for (int i = 1; i <= ft.size(); ++i) {
                Std_out::print(ft.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0] == "set") {
            ft = Fenwick_tree{line.size() - 1};
            for (int i = 1; i <= line.size() - 1; ++i) {
                ft.update(i, utility::str_to_num(line[i]));
            }
        } else if (line[0] == "up") {
            ft.update(arg1, arg2);
            for (int i = 1; i <= ft.size(); ++i) {
                Std_out::print(ft.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0] == "rsq") {
            Std_out::printf("Sum from %d to %d = %d%n", arg1, arg2, ft.rsq(arg1, arg2));
        } else {
            Std_out::print_line("Invalid command");
        }
    }

    Std_out::close();
    return 0;
}