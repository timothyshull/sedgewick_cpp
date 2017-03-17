#include "Sparse_vector.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Sparse_vector a{10};
    Sparse_vector b{10};
    a.put(3, 0.50);
    a.put(9, 0.75);
    a.put(6, 0.11);
    a.put(6, 0.00);
    b.put(3, 0.60);
    b.put(4, 0.90);
    Std_out::print_line("a = " + a);
    Std_out::print_line("b = " + b);
    Std_out::print_line("a dot b = " + a.dot(b));
    Std_out::print_line("a + b   = " + a.plus(b));
    return 0;
}