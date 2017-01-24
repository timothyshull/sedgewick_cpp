int main(int argc, char *argv[]) {
    Out out;

    // write to stdout
    out = new Out();
    out.print_line("Test 1");
    out.close();

    // write to a file
    out = new Out("test.txt");
    out.print_line("Test 2");
    out.close();
    return 0;
}