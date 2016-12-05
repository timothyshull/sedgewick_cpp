#include <iostream>
#include <fstream>

#include "Timer.h"
#include "sort.h"

std::string &read_input_file(const char *fname, std::string &s) {
    std::ifstream f;
    f.open(fname);
    if (!f) {
        std::cerr << "Unable to open " << fname << "\n";
        std::exit(1);
    }

    std::istream::pos_type fpos = f.tellg();
    if (-1 == fpos) {
        std::cerr << "Error reading size of " << fname << "\n";
        std::exit(1);
    }
    f.seekg(0, std::istream::end);
    std::streamoff len = f.tellg() - fpos;
    if (len == -1) {
        std::cerr << "Error reading size of " << fname << "\n";
        std::exit(1);
    }
    f.seekg(fpos);
    s.resize(static_cast<std::string::size_type>(len));
    f.read(&s[0], s.length());
    return s;
}

int main(int argc, char *argv[]) {
    const char *filename = argv[1];
    int num_trials = atoi(argv[2]);

    std::string fcontents;
    fcontents = read_input_file(filename, fcontents);

    Timer t;
    double total{0.0};
    for (int i = 0; i < num_trials; i++) {
        std::string tmp{fcontents};
        t.reset();
        t.start_timer();
        sort(tmp);
        total += t.get_elapsed_millis();
    }
    std::cout << "The average running time for this sort was: " << total / static_cast<double>(num_trials) << "\n";

    return 0;
}