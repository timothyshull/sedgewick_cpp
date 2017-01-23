int main(int argc, char *argv[]) {
    String filename = args[0];
    BinaryOut out = new BinaryOut(filename);
    BinaryIn in = new BinaryIn();

    // read from standard input and write to file
    while (!in.isEmpty()) {
        char c = in.readChar();
        out.write(c);
    }
    out.flush();
}