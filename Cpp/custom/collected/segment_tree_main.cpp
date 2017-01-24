int main(int argc, char *argv[]) {
    SegmentTree st = null;

    std::string cmd = "cmp";
    while (true) {
        String[] line = Std_in::read_line().split(" ");

        if (line[0].equals("exit")) break;

        int arg1 = 0, arg2 = 0, arg3 = 0;

        if (line.length > 1) {
            arg1 = Integer.parseInt(line[1]);
        }
        if (line.length > 2) {
            arg2 = Integer.parseInt(line[2]);
        }
        if (line.length > 3) {
            arg3 = Integer.parseInt(line[3]);
        }

        if ((!line[0].equals("set") && !line[0].equals("init")) && st == null) {
            Std_out::print_line("Segment Tree not initialized");
            continue;
        }
        int array[];
        if (line[0].equals("set")) {
            array = new int[line.length - 1];
            for (int i = 0; i < line.length - 1; ++i) {
                array[i] = Integer.parseInt(line[i + 1]);
            }
            st = new SegmentTree(array);
        } else if (line[0].equals("init")) {
            array = new int[arg1];
            Arrays.fill(array, arg2);
            st = new SegmentTree(array);

            for (int i = 0; i < st.size(); ++i) {
                Std_out::print(st.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0].equals("up")) {
            st.update(arg1, arg2, arg3);
            for (int i = 0; i < st.size(); ++i) {
                Std_out::print(st.rsq(i, i) + " ");
            }
            Std_out::print_line();
        } else if (line[0].equals("rsq")) {
            Std_out::printf("Sum from %d to %d = %d%n", arg1, arg2, st.rsq(arg1, arg2));
        } else if (line[0].equals("rmq")) {
            Std_out::printf("Min from %d to %d = %d%n", arg1, arg2, st.rMinQ(arg1, arg2));
        } else {
            Std_out::print_line("Invalid command");
        }

    }


    Std_out::close();
    return 0;
}