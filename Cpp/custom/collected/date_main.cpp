int main(int argc, char *argv[]) {
    Date today = new Date(2, 25, 2004);
    StdOut.println(today);
    for (int i = 0; i < 10; i++) {
        today = today.next();
        StdOut.println(today);
    }

    StdOut.println(today.isAfter(today.next()));
    StdOut.println(today.isAfter(today));
    StdOut.println(today.next().isAfter(today));


    Date birthday = new Date(10, 16, 1971);
    StdOut.println(birthday);
    for (int i = 0; i < 10; i++) {
        birthday = birthday.next();
        StdOut.println(birthday);
    }
    return 0;
}