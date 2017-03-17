#include <string>
#include <vector>
#include "LZW_compression.h"
#include "Binary_std_in.h"
#include "Binary_std_out.h"
#include "TST.h"

void ::LZW_compression::compress()
{
    std::string input{Binary_std_in::read_string()};
    TST<int> st;
    std::string s;
    for (int i{0}; i < radix; ++i) {
        s = static_cast<char>(i);
        st.put(s, i);
    }
    int code{radix + 1};

    std::string prefix;
    std::string sub;
    while (input.length() > 0) {
        prefix = st.longestPrefixOf(input);
        Binary_std_out::write(st.get(s), codeword_width);
        auto t = s.length();
        if (t < input.length() && code < num_codewords) {
            sub = input.substr(0, t + 1);
            st.put(sub, code++);
        }
        input = input.substr(t);
    }
    Binary_std_out::write(radix, codeword_width);
    Binary_std_out::close();
}

void ::LZW_compression::expand()
{
    std::vector<std::string> st;
    st.reserve(static_cast<std::vector<std::string>::size_type>(num_codewords));
    int i;

    std::string ch;
    for (i = 0; i < radix; ++i) {
        ch = static_cast<char>(i);
        st[i] = ch;
    }
    st[i++] = "";

    int codeword{Binary_std_in::read_int(codeword_width)};
    if (codeword == radix) { return; }
    std::string val{st[codeword]};

    while (true) {
        Binary_std_out::write(val);
        codeword = Binary_std_in::read_int(codeword_width);
        if (codeword == radix) { break; }
        std::string s = st[codeword];
        if (i == codeword) { s = val + val[0]; }
        if (i < num_codewords) { st[i++] = val + s[0]; }
        val = s;
    }
    Binary_std_out::close();
}
