#include "utility.h"
#include "Huffman.h"

int main(int argc, char* argv[])
{
    if (argv[1] == "-") {
        Huffman::compress();
    } else if (argv[2] == "+") {
        Huffman::expand();
    } else {
        throw utility::Illegal_argument_exception("Illegal command line argument");
    }
    return 0;
}