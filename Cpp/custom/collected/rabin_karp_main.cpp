int main(int argc, char *argv[]) {
    std::string pat = argv[1];
    std::string txt = argv[2];

    RabinKarp searcher = new RabinKarp(pat);
    int offset = searcher.search(txt);

    // print results
    Std_out::print_line("text:    " + txt);

    // from brute force search method 1
    Std_out::print("pattern: ");
    for (int i = 0; i < offset; ++i)
        Std_out::print(" ");
    Std_out::print_line(pat);
    return 0;
}