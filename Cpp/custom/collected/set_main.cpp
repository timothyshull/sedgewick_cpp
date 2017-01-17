#include <iostream>
#include <string>

#include "Set.h"

int main()
{
    Set<std::string> s{};

    s.add("www.cs.princeton.edu");
    s.add("www.cs.princeton.edu");
    s.add("www.princeton.edu");
    s.add("www.math.princeton.edu");
    s.add("www.yale.edu");
    s.add("www.amazon.com");
    s.add("www.simpsons.com");
    s.add("www.stanford.edu");
    s.add("www.google.com");
    s.add("www.ibm.com");
    s.add("www.apple.com");
    s.add("www.slashdot.com");
    s.add("www.whitehouse.gov");
    s.add("www.espn.com");
    s.add("www.snopes.com");
    s.add("www.movies.com");
    s.add("www.cnn.com");
    s.add("www.iitb.ac.in");

    std::cout << std::boolalpha << s.contains("www.cs.princeton.edu") << "\n";
    std::cout << s.contains("www.cs.princeton.edu") << "\n";

    std::cout << !s.contains("www.harvardsucks.com");
    std::cout << s.contains("www.simpsons.com");
    std::cout << "\n";

    std::cout << "ceiling(www.simpsonr.com) = " << s.ceiling("www.simpsonr.com") << "\n";
    std::cout << "ceiling(www.simpsons.com) = " << s.ceiling("www.simpsons.com") << "\n";
    std::cout << "ceiling(www.simpsont.com) = " << s.ceiling("www.simpsont.com") << "\n";
    std::cout << "floor(www.simpsonr.com)   = " << s.floor("www.simpsonr.com") << "\n";
    std::cout << "floor(www.simpsons.com)   = " << s.floor("www.simpsons.com") << "\n";
    std::cout << "floor(www.simpsont.com)   = " << s.floor("www.simpsont.com") << "\n";
    std::cout << "\n";


    // print out all keys in this set in lexicographic order
    for (auto k : s) {
        std::cout << k << "\n";
    }

    std::cout << "\n";
    Set<std::string> set2{set};
    std::cout << s.equals(set2));

    return 0;
}
