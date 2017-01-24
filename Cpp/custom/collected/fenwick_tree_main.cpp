int main(int argc, char *argv[]) {
    FenwickTree ft = null;

    std::string cmd = "cmp";
    while (true) {
        String[] line = Std_in::read_line().split(" ");

        if (line[0].equals("exit")) break;

        int arg1 = 0, arg2 = 0;

        if (line.length > 1) {
            arg1 = Integer.parseInt(line[1]);
        }
        if (line.length > 2) {
            arg2 = Integer.parseInt(line[2]);
        }

        if ((!line[0].equals("set") && !line[0].equals("init")) && ft == null) {
            Std_out::print_line("FenwickTree not initialized");
            continue;
        }

        if (line[0].equals("init")) {
            ft = new FenwickTree(arg1);
            for (int i = 1; i <= ft.size(); ++i) {
                Std_out::print(ft.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0].equals("set")) {
            ft = new FenwickTree(line.length - 1);
            for (int i = 1; i <= line.length - 1; ++i) {
                ft.update(i, Integer.parseInt(line[i]));
            }
        } else if (line[0].equals("up")) {
            ft.update(arg1, arg2);
            for (int i = 1; i <= ft.size(); ++i) {
                Std_out::print(ft.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0].equals("rsq")) {
            Std_out::printf("Sum from %d to %d = %d%n", arg1, arg2, ft.rsq(arg1, arg2));
        } else {
            Std_out::print_line("Invalid command");
        }

    }


    Std_out::close();
    return 0;
}