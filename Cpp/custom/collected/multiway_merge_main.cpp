int main(int argc, char *argv[]) {
    int n = args.length;
    In[] streams = new In[n];
    for (int i = 0; i < n; i++)
        streams[i] = new In(args[i]);
    merge(streams);
    return 0;
}