#include<iostream>
#include<cstdlib>
#include<cmath>
#include<random>

using std::cin;
using std::cout;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;

template<typename Number = int>
Number random_number()
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<Number> uniform_dist(0, RAND_MAX);
    return uniform_dist(gen);
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    float m1 = 0.0;
    float m2 = 0.0;
    for (int i = 0; i < n; i++) {
        auto x = random_number();
        m1 += static_cast<float>(x) / n;
        m2 += static_cast<float>(x * x) / n;
    }
    cout << "     Avg.: " << m1 << "\n";
    cout << "Std. dev.: " << sqrt(m2 - m1 * m1) << "\n";
    return 0;
}

