#ifndef COLLECTED_RADIX_UTIL_H
#define COLLECTED_RADIX_UTIL_H

#include <climits>
#include <limits>

short bits_per_byte = CHAR_BIT;

short bits_per_word = WORD_BIT;

short bytes_per_word = WORD_BIT / CHAR_BIT;

int radix = std::numeric_limits<char>::max();

// page 421
inline int digit(long a, int b) { return static_cast<int>(a >> bits_per_byte * (bytes_per_word - b - 1) & (radix - 1)); } // narrow_cast
inline int digit(char* a, int b) { return a[b]; }

template<typename Item_type>
inline int digit(Item_type& a, int b) { return a.to_string[b]; } // or std::to_string

#endif // COLLECTED_RADIX_UTIL_H
