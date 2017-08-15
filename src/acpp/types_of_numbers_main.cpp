// Program 3.2 - Types of numbers
#include <iostream>
#include <random>

int random_number()
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> uniform_dist{0, std::numeric_limits<int>::max()};
    return uniform_dist(gen);
}

int main(int argc, char* argv[])
{
    auto n = std::stoi(argv[1]);
    float m1{0.0};
    float m2{0.0};

    for (auto i = 0; i < n; ++i) {
        auto x = random_number();
        m1 += static_cast<float>(x) / n;
        m2 += static_cast<float>(x * x) / n;
    }

    std::cout << "     Avg.: " << m1 << "\n";
    std::cout << "Std. dev.: " << sqrt(m2 - m1 * m1) << "\n";
    return 0;
}
