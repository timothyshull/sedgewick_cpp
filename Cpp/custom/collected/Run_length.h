#ifndef RUN_LENGTH_H
#define RUN_LENGTH_H

namespace Run_length {
    const static int R = 256;
    const static int LG_R = 8;

    void expand();
    void compress();

};

#endif // RUN_LENGTH_H
