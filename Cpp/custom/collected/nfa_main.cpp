int main(int argc, char *argv[]) {
    std::string regexp = "(" + argv[1] + ")";
    std::string txt = argv[1];
    NFA nfa = new NFA(regexp);
    Std_out::print_line(nfa.recognizes(txt));
    return 0;
}