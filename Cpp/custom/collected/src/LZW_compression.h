#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

namespace LZW_compression {
    const static int radix = 256;
    const static int num_codewords = 4096;
    const static int codeword_width = 12;

    void compress();

    void expand();
};

#endif // LZW_COMPRESSION_H
