#include "utility.h"
#include "Run_length.h"

int main(int argc, char* argv[])
{
    if (std::string{argv[1]} == "-") { Run_length::compress(); }
    else if (std::string{argv[1]} == "+") { Run_length::expand(); }
    else { throw utility::Illegal_argument_exception{"Illegal command line argument"}; }
    return 0;
}