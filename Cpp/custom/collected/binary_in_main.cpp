int main(int argc, char *argv[]) {
    BinaryIn in = new BinaryIn(args[0]);
    BinaryOut out = new BinaryOut(args[1]);

    // read one 8-bit char at a time
    while (!in.isEmpty()) {
        char c = in.readChar();
        out.write(c);
    }
    out.flush();
    return 0;
}