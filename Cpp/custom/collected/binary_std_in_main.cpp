

int main(int argc, char *argv[]) {
    while (!BinaryStdIn.isEmpty()) {
        char c = BinaryStdIn.readChar();
        BinaryStdOut.write(c);
    }
    BinaryStdOut.flush();
    return 0;
}