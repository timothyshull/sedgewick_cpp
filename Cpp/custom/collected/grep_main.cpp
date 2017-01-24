int main(int argc, char *argv[]) {
    std::string regexp = "(.*" + argv[1] + ".*)";
    NFA nfa = new NFA(regexp);
    while (Std_in::hasNextLine()) {
        std::string line = Std_in::read_line();
        if (nfa.recognizes(line)) {
            Std_out::print_line(line);
        }
    }
    return 0;
}