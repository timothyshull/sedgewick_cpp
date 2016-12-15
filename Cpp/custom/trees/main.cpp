#include <iostream>

template<typename Value_type>
struct test {
    using Value_type = Value_type;
};

int main() {
    typename test<int>::Value_type tmp{10};
    std::cout << "Hello, World!" << std::endl;
    return 0;
}