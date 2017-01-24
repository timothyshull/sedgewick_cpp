int main(int argc, char *argv[]) {
    int n = argc;
    In[] streams = new In[n];
    for (int i = 0; i < n; ++i)
        streams[i] = new In(argv[i]);
    merge(streams);
    return 0;
}