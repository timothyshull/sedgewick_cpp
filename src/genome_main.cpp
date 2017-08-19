#include "Genome.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    if (argv[1] == "-") {
        Genome::compress();
    } else if (argv[1] == "+") {
        Genome::expand();
    } else {
        throw utility::Illegal_argument_exception{"Illegal command line argument"};
    }
    return 0;
}