int main(int argc, char *argv[]) {
    String regexp = "(" + args[0] + ")";
    String txt = args[1];
    NFA nfa = new NFA(regexp);
    StdOut.println(nfa.recognizes(txt));
    return 0;
}