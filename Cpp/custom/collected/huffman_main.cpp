int main(int argc, char *argv[]) {
    if (args[0].equals("-")) compress();
    else if (args[0].equals("+")) expand();
    else throw new IllegalArgumentException("Illegal command line argument");
    return 0;
}