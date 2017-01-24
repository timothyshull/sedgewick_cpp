int main(int argc, char *argv[]) {
    In in{argv[1]};
    std::vector<int> a = in.readAllInts();
    int count = count(a);
    Std_out::print_line(count);
    return 0;
}