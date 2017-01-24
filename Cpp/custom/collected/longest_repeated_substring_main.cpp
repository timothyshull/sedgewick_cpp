int main(int argc, char *argv[]) {
    std::string text = Std_in::readAll().replaceAll("\\s+", " ");
    Std_out::print_line("'" + lrs(text) + "'");
    return 0;
}