#include <vector>

#include "Alphabet.h"
#include "Std_out.h"

int main()
{
    auto encoded1 = Alphabets::base64.to_indices("NowIsTheTimeForAllGoodMen");
    auto decoded1 = Alphabets::base64.to_chars(encoded1);
    Std_out::print_line(decoded1);

    auto encoded2 = Alphabets::dna.to_indices("AACGAACGGTTTACCCCG");
    auto decoded2 = Alphabets::dna.to_chars(encoded2);
    Std_out::print_line(decoded2);

    auto encoded3 = Alphabets::decimal.to_indices("01234567890123456789");
    auto decoded3 = Alphabets::decimal.to_chars(encoded3);
    Std_out::print_line(decoded3);

    return 0;
}