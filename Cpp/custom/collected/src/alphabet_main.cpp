#include <vector>

#include "Alphabet.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<int> encoded1 = Alphabets::base64.to_indices("NowIsTheTimeForAllGoodMen");
    std::string decoded1 = Alphabets::base64.to_chars(encoded1);
    Std_out::print_line(decoded1);

    std::vector<int> encoded2 = Alphabets::dna.to_indices("AACGAACGGTTTACCCCG");
    std::string decoded2 = Alphabets::dna.to_chars(encoded2);
    Std_out::print_line(decoded2);

    std::vector<int> encoded3 = Alphabets::decimal.to_indices("01234567890123456789");
    std::string decoded3 = Alphabets::decimal.to_chars(encoded3);
    Std_out::print_line(decoded3);

    return 0;
}