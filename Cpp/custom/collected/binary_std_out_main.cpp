#include "utility.h"
#include "Binary_std_out.h"

int main(int argc, char* argv[])
{
    int m = utility::safe_convert_integer(argv[1]);

    for (int i = 0; i < m; ++i) {
        Binary_std_out::write(i);
    }
    Binary_std_out::flush();
    return 0;
}