int main(int argc, char *argv[]) {
    String regexp = "(.*" + args[0] + ".*)";
    NFA nfa = new NFA(regexp);
    while (StdIn.hasNextLine()) {
        String line = StdIn.readLine();
        if (nfa.recognizes(line)) {
            StdOut.println(line);
        }
    }
    return 0;
}