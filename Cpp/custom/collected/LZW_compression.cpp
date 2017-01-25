#include "LZW_compression.h"

void ::LZW_compression::compress()
{
    std::string input = Binary_std_in::read_string();
    TST <Integer> st = new TST<Integer>();
    for (int i{0}; i < R; ++i) {
        st.put("" + (char) i, i);
    }
    int code = R + 1;  // R is codeword for EOF

    while (input.length() > 0) {
        std::string s = st.longestPrefixOf(input);  // Find max prefix match s.
        Binary_std_out::write(st.get(s), W);      // Print s's encoding.
        int t = s.length();
        if (t < input.length() && code < L) {    // Add s to symbol table.
            st.put(input.substring(0, t + 1), code++);
        }
        input = input.substring(t);            // Scan past s in input.
    }
    Binary_std_out::write(R, W);
    Binary_std_out::close();
}

void ::LZW_compression::expand()
{
    std::vector<std::string> st = new String[L];
    int i; // next available codeword value

    // initialize symbol table with all 1-character strings
    for (i = 0; i < R; ++i) {
        st[i] = "" + (char) i;
    }
    st[i++] = "";                        // (unused) lookahead for EOF

    int codeword = Binary_std_in::read_int(W);
    if (codeword == R) { return; }           // expanded message is empty string
    std::string val = st[codeword];

    while (true) {
        Binary_std_out::write(val);
        codeword = Binary_std_in::read_int(W);
        if (codeword == R) break;
        std::string s = st[codeword];
        if (i == codeword) s = val + val.charAt(0);   // special case hack
        if (i < L) st[i++] = val + s.charAt(0);
        val = s;
    }
    Binary_std_out::close();
}
