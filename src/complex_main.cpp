#include "Std_out.h"
#include "Complex.h"

int main(int argc, char* argv[])
{
    Complex a{5.0, 6.0};
    Complex b{-3.0, 4.0};

    Std_out::print("a            = ");
    Std_out::print(a);
    Std_out::print("b            = ");
    Std_out::print(b);
    Std_out::printf("Re(a)        = %f\n", a.real());
    Std_out::printf("Im(a)        = %f\n", a.imaginary());
    Std_out::print("b + a        = ");
    Std_out::print(b.plus(a));
    Std_out::print("a - b        = ");
    Std_out::print(a.minus(b));
    Std_out::print("a * b        = ");
    Std_out::print(a.times(b));
    Std_out::print("b * a        = ");
    Std_out::print(b.times(a));
    Std_out::print("a / b        = ");
    Std_out::print(a.divides(b));
    Std_out::print("(a / b) * b  = ");
    Std_out::print(a.divides(b).times(b));
    Std_out::print("conj(a)      = ");
    Std_out::print(a.conjugate());
    Std_out::printf("|a|          = %f\n", a.abs());
    Std_out::print("tan(a)       = ");
    Std_out::print(a.tan());
    return 0;
}
