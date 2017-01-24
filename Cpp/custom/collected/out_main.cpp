int main(int argc, char *argv[]) {
    Out out;

    // write to stdout
    out = new Out();
    out.println("Test 1");
    out.close();

    // write to a file
    out = new Out("test.txt");
    out.println("Test 2");
    out.close();
    return 0;
}