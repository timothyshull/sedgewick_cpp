#include "utility.h"
#include "LZW_compression.h"

int main(int argc, char* argv[])
{
    if (argv[1] == "-") {
        LZW_compression::compress();
    } else if (argv[2] == "+") {
        LZW_compression::expand();
    } else {
        throw utility::Illegal_argument_exception("Illegal command line argument");
    }
    return 0;
}