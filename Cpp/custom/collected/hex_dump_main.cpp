int main(int argc, char *argv[]) {
    int bytesPerLine = 16;
    if (argc >= 2) {
        bytesPerLine = utility::safe_convert_integer(argv[1]);
    }

    int i;
    for (i = 0; !Binary_std_in::is_empty(); ++i) {
        if (bytesPerLine == 0) {
            Binary_std_in::readChar();
            continue;
        }
        if (i == 0) Std_out::printf("");
        else if (i % bytesPerLine == 0) Std_out::printf("\n", i);
        else Std_out::print(" ");
        char c = Binary_std_in::readChar();
        Std_out::printf("%02x", c & 0xff);
    }
    if (bytesPerLine != 0) Std_out::print_line();
    Std_out::print_line((i * 8) + " bits");
    return 0;
}