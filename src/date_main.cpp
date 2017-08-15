#include "Std_out.h"
#include "Date.h"

int main(int argc, char* argv[])
{
    Date today{2, 25, 2004};
    Std_out::print_line(today);
    for (auto i = 0; i < 10; ++i) {
        today = today.next();
        Std_out::print_line(today);
    }

    Std_out::print_line(today.is_after(today.next()));
    Std_out::print_line(today.is_after(today));
    Std_out::print_line(today.next().is_after(today));

    Date birthday{10, 16, 1971};
    Std_out::print_line(birthday);
    for (auto i = 0; i < 10; ++i) {
        birthday = birthday.next();
        Std_out::print_line(birthday);
    }
    return 0;
}