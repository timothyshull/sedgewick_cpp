#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

namespace LZW_compression {
    const static int R = 256;
    const static int L = 4096;
    const static int W = 12;

    void compress();

    void expand();
};

#endif // LZW_COMPRESSION_H
