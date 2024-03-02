#include <gtest/gtest.h>

#include <array>
#include <iostream>
#include <vector>

extern int solution(int D, int P, int Q);

TEST(Test1214, tc1) {
    EXPECT_EQ(solution(17, 7, 13), 20);
}

TEST(Test1214, tc2) {
    EXPECT_EQ(solution(21, 7, 13), 21);
}

TEST(Test1214, tc3) {
    EXPECT_EQ(solution(17, 7, 9), 18);
}

TEST(Test1214, tc4) {
    EXPECT_EQ(solution(37, 9, 17), 43);
}

TEST(Test1214, tc5) {
    EXPECT_EQ(solution(287341, 2345, 7253), 287398);
}

TEST(Test1214, tc6) {
    EXPECT_EQ(solution(1, 2, 3), 2);
}

TEST(Test1214, tc7) {
    EXPECT_EQ(solution(1, 3, 2), 2);
}

TEST(Test1214, tc8) {
    EXPECT_EQ(solution(5, 3, 1), 5);
}

TEST(Test1214, tc9) {
    EXPECT_EQ(solution(10, 4, 6), 10);
}

TEST(Test1214, tc10) {
    EXPECT_EQ(solution(11, 4, 6), 12);
}

TEST(Test1214, tc11) {
    EXPECT_EQ(solution(11, 4, 4), 12);
}

TEST(Test1214, tc12) {
    EXPECT_EQ(solution(12, 4, 4), 12);
}

TEST(Test1214, tc13) {
    EXPECT_EQ(solution(121, 10, 9), 121);
}

TEST(Test1214, tc14) {
    EXPECT_EQ(solution(1000000000, 2, 99999999), 1000000000);
}