// Program 3.15 - String search
#include "string_search.h"

int string_search(std::string& search_str, std::string& target)
{
    int i;
    int j;
    for (i = 0; i < target.size(); ++i) {
        for (j = 0; j < search_str.size(); ++j) {
            if (target[i + j] != search_str[j]) { break; }
        }
        if (j == search_str.size()) { return j; }
    }
    return -1;
}
