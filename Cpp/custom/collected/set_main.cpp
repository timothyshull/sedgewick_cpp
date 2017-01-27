#include "Set.h"
#include "Std_out.h"

int main()
{
    Set<std::string> set;

    set.add("www.cs.princeton.edu");
    set.add("www.cs.princeton.edu");
    set.add("www.princeton.edu");
    set.add("www.math.princeton.edu");
    set.add("www.yale.edu");
    set.add("www.amazon.com");
    set.add("www.simpsons.com");
    set.add("www.stanford.edu");
    set.add("www.google.com");
    set.add("www.ibm.com");
    set.add("www.apple.com");
    set.add("www.slashdot.com");
    set.add("www.whitehouse.gov");
    set.add("www.espn.com");
    set.add("www.snopes.com");
    set.add("www.movies.com");
    set.add("www.cnn.com");
    set.add("www.iitb.ac.in");

    Std_out::print_line(set.contains("www.cs.princeton.edu"));
    Std_out::print_line(!set.contains("www.harvardsucks.com"));
    Std_out::print_line(set.contains("www.simpsons.com"));
    Std_out::print_line();

    Std_out::print_line("ceiling(www.simpsonr.com) = " + set.ceiling("www.simpsonr.com"));
    Std_out::print_line("ceiling(www.simpsons.com) = " + set.ceiling("www.simpsons.com"));
    Std_out::print_line("ceiling(www.simpsont.com) = " + set.ceiling("www.simpsont.com"));
    Std_out::print_line("floor(www.simpsonr.com)   = " + set.floor("www.simpsonr.com"));
    Std_out::print_line("floor(www.simpsons.com)   = " + set.floor("www.simpsons.com"));
    Std_out::print_line("floor(www.simpsont.com)   = " + set.floor("www.simpsont.com"));
    Std_out::print_line();

    for (auto s : set) {
        Std_out::print_line(s);
    }

    Std_out::print_line();
    Set<std::string> set2{set};
    Std_out::print_line(set == set2);

    return 0;
}
