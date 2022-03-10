#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <iostream>
#include <string>
#include <sstream>

extern void run_test(std::istream& is, std::ostream& os);

TEST(TC, TC1)
{
    std::stringstream input("10 4 10");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("2", output.str());
}

TEST(TC, TC2)
{
    std::stringstream input("2 1 2");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("-1", output.str());
}

TEST(TC, TC3)
{
    std::stringstream input("7 2 6");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("2", output.str());
}

TEST(TC, TC4)
{
    std::stringstream input("150 1 85");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("6", output.str());
}

TEST(TC, TC5)
{
    std::stringstream input("23 2 22");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("4", output.str());
}

TEST(TC, TC6)
{
    std::stringstream input("21 1 21");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("-1", output.str());
}

TEST(TC, TC7)
{
    std::stringstream input("5 1 5");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("-1", output.str());
}

auto invert_bit(auto v) {
    return std::bit_ceil(v + 1) - v - 1;
}

TEST(TC, UNIT1)
{
    EXPECT_EQ(0, invert_bit(1u));
    EXPECT_EQ(1, invert_bit(2u));
    EXPECT_EQ(0, invert_bit(3u));
    EXPECT_EQ(3, invert_bit(4u));
    EXPECT_EQ(2, invert_bit(5u));
    EXPECT_EQ(1, invert_bit(6u));
    EXPECT_EQ(0, invert_bit(7u));
}

auto overflow_length(auto v) {
    return 2 * v - std::bit_ceil(v + 1) + 1;
}

TEST(TC, UNIT2)
{
    EXPECT_EQ(1, overflow_length(1u));
    EXPECT_EQ(1, overflow_length(2u));
    EXPECT_EQ(3, overflow_length(3u));
    EXPECT_EQ(1, overflow_length(4u));
    EXPECT_EQ(3, overflow_length(5u));
    EXPECT_EQ(5, overflow_length(6u));
    EXPECT_EQ(7, overflow_length(7u));
    EXPECT_EQ(1, overflow_length(8u));
    EXPECT_EQ(3, overflow_length(9u));
    EXPECT_EQ(5, overflow_length(10u));
    EXPECT_EQ(7, overflow_length(11u));
    EXPECT_EQ(9, overflow_length(12u));
    EXPECT_EQ(11, overflow_length(13u));
    EXPECT_EQ(13, overflow_length(14u));
    EXPECT_EQ(15, overflow_length(15u));
}

