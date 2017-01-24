#include "In.h"
#include "Set.h"
#include "Std_out.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    Set<std::string> set{};

    In in{argv[1]};
    while (!in.is_empty()) {
        std::string word = in.read_string();
        set.add(word);
    }

    while (!Std_in::is_empty()) {
        std::string word = Std_in::read_string();
        if (!set.contains(word)) {
            Std_out::print_line(word);
        }
    }
    return 0;
}