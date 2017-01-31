#include <Accumulator.h>
#include <gtest/gtest.h>

//TEST(MyString, DefaultConstructor) {
//    const MyString s;
//
//    EXPECT_STREQ(NULL, s.c_string());
//
//    EXPECT_EQ(0u, s.Length());
//}
//
//const char kHelloString[] = "Hello, world!";
//
//TEST(MyString, ConstructorFromCString) {
//    const MyString s(kHelloString);
//    EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
//    EXPECT_EQ(sizeof(kHelloString)/sizeof(kHelloString[0]) - 1,
//              s.Length());
//}
//
//TEST(MyString, CopyConstructor) {
//    const MyString s1(kHelloString);
//    const MyString s2 = s1;
//    EXPECT_EQ(0, strcmp(s2.c_string(), kHelloString));
//}
//
//TEST(MyString, Set) {
//    MyString s;
//
//    s.Set(kHelloString);
//    EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
//
//    s.Set(s.c_string());
//    EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
//
//    s.Set(NULL);
//    EXPECT_STREQ(NULL, s.c_string());
//}

TEST(Accumulator, DefaultConstructor)
{
    Accumulator<double> stats;
    EXPECT_EQ(0, stats.count());
    EXPECT_EQ(0.0, stats.mean());
    EXPECT_EQ(0.0, stats.std_dev());
    EXPECT_EQ(0.0, stats.var());
}

TEST(Accumulator, count) {
    Accumulator<double> stats;
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    std::clog << "Should have added 5 values\n";
    EXPECT_EQ(5, stats.count());
}