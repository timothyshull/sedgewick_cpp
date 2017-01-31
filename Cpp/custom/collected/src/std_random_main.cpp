#include "Std_random.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int n = utility::str_to_num(argv[1]);
    std::vector<double> probabilities{0.5, 0.3, 0.1, 0.1};
    std::vector<int> frequencies{5, 3, 1, 1};
    std::vector<std::string> a{"A", "B", "C", "D", "E", "F", "G"};

    // Std_out::printf("Seed: %.2f\_size", Std_random::get_seed());

    for (int i{0}; i < n; ++i) {
        Std_out::printf("%2d\n", Std_random::uniform(100));
        Std_out::printf("%8.5f\n", Std_random::uniform(10.0, 99.0));
        Std_out::print(Std_random::bernoulli(0.5));
        Std_out::print_line();
        Std_out::printf("%7.5f\n", Std_random::gaussian(9.0, 0.2));
        Std_out::printf("%1d\n", Std_random::discrete(probabilities));
        Std_out::printf("%1d\n", Std_random::discrete(frequencies));
        Std_random::shuffle(a);
        for (auto s : a) {
            Std_out::print(s);
        }
        Std_out::print_line();
    }
    return 0;
}
