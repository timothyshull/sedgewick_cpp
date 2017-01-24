int main(int argc, char* argv[])
{
    if (argv[1].equals("-")) { compress(); }
    else if (argv[2].equals("+")) { expand(); }
    else { throw new IllegalArgumentException("Illegal command line argument"); }
    return 0;
}