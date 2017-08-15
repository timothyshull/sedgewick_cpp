#include "In.h"

void ::In_tests::test1(std::string&& filename)
{
    In<std::ifstream> in{filename};

    while (in.has_next_line()) {
        std::string line = in.read_line();
        std::cerr << "The next line is: " << line << "\n";
    }
    in.close();
    std::cerr << "test 1 passed\n";
}

void ::In_tests::test2(std::string&& filename)
{
    In<std::ifstream> in{filename};

    while (!in.is_empty()) {
        std::string line = in.read_line();
        std::cerr << "The next line is: " << line << "\n";
    }
    in.close();
    std::cerr << "test 2 passed\n";
}

void ::In_tests::test3(std::string&& filename)
{
    In<std::ifstream> in{filename};

    std::vector<double> all_doubles{in.read_all_doubles()};

    for (auto d : all_doubles) {
        std::cerr << d << "\n";
    }
    in.close();
    std::cerr << "test 3 passed\n";
}

void ::In_tests::test4(std::string&& filename)
{
    In<std::ifstream> in{filename};
    while (in.has_next_char()) {
        std::cerr << in.read_char() << "\n";
    }
    in.close();
    std::cerr << "test 4 passed\n";
}

void ::In_tests::test5(std::string&& filename)
{
    In<std::ifstream> in{filename};
    std::string str{in.read_all()};
    std::cerr << "The whole file:\n" << str << "\n";
    in.close();
    std::cerr << "test 5 passed\n";
}

void ::In_tests::test6(std::string&& filename)
{
    In<std::ifstream> in{filename};
    auto i = in.read_int();
    float f{in.read_float()};
    double d{in.read_double()};
    short s{in.read_short()};
    long l{in.read_long()};
    bool bt{in.read_boolean()};
    bool bf{in.read_boolean()};

    std::cerr << "int: " << i << ", float: " << f << ", double: " << d << ", short: " << s << ", long: " << l
              << ", bool true: " << std::boolalpha << bt << ", bool false: " << bf << "\n";
    in.close();
    std::cerr << "test 6 passed\n";
}

// Start Async_io tests
void ::In_tests::test7(std::string&& url_name)
{
    In<Async_iostream> in{url_name};
    std::cerr << "test 7 passed\n";

    while (!in.is_empty()) {
        std::string line = in.read_line();
        std::cerr << "The next line is: " << line << "\n";
    }
    in.close();
    std::cerr << "test 7 passed\n";
}

void ::In_tests::test8(std::string&& filename)
{
    In<Async_iostream> in{filename};
    std::cerr << "test 8 passed\n";
}
