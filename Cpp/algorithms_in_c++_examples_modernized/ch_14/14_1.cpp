int hash(char* v, int M)
{
    int h = 0, a = 127;
    for (; *v != 0; ++v) {
        h = (a * h + *v) % M;
    }
    return h;
}

