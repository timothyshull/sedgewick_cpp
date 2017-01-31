#include "B_tree.h"
#include "Std_out.h"

int main()
{
    B_tree<std::string, std::string> st{};

    st.put("www.cs.princeton.edu", "128.112.136.12");
    st.put("www.cs.princeton.edu", "128.112.136.11");
    st.put("www.princeton.edu", "128.112.128.15");
    st.put("www.yale.edu", "130.132.143.21");
    st.put("www.simpsons.com", "209.052.165.60");
    st.put("www.apple.com", "17.112.152.32");
    st.put("www.amazon.com", "207.171.182.16");
    st.put("www.ebay.com", "66.135.192.87");
    st.put("www.cnn.com", "64.236.16.20");
    st.put("www.google.com", "216.239.41.99");
    st.put("www.nytimes.com", "199.239.136.200");
    st.put("www.microsoft.com", "207.126.99.140");
    st.put("www.dell.com", "143.166.224.230");
    st.put("www.slashdot.org", "66.35.250.151");
    st.put("www.espn.com", "199.181.135.201");
    st.put("www.weather.com", "63.111.66.11");
    st.put("www.yahoo.com", "216.109.118.65");

    Std_out::print_line("cs.princeton.edu:  " + *st.get("www.cs.princeton.edu"));
    Std_out::print_line("hardvardsucks.com: " + *st.get("www.harvardsucks.com"));
    Std_out::print_line("simpsons.com:      " + *st.get("www.simpsons.com"));
    Std_out::print_line("apple.com:         " + *st.get("www.apple.com"));
    Std_out::print_line("ebay.com:          " + *st.get("www.ebay.com"));
    Std_out::print_line("dell.com:          " + *st.get("www.dell.com"));
    Std_out::print_line();

    Std_out::printf("size:    %d\n", st.size());
    Std_out::printf("height:  %d\n", st.height());
    Std_out::print_line(st);
    Std_out::print_line();
    return 0;
}
