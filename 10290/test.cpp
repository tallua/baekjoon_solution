#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <iostream>
#include <string>
#include <sstream>

extern void run_test(std::istream& is, std::ostream& os);

TEST(TC, TC1)
{
    std::stringstream input(R"(
        10 7 8
        ELIPMOCN
        TACODEOL
        IMELBORP
        MGOALRRM
        BIPLEIEA
        UCATZUCE
        SBHEMSTT
        BAPC
        TUE
        TEAM
        PROBLEM
        CODE
        COMPILE
        SUBMIT
        CORRECT
        BALLOON
        PRIZE
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("ALGORITHMS", output.str());
}

TEST(TC, TC2)
{
    std::stringstream input(R"(
        2 4 3
        BCB
        AOA
        PDP
        CEC
        BAPC
        CODE
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("ambiguous", output.str());
}

TEST(TC, TC3)
{
    std::stringstream input(R"(
        3 4 3
        BCB
        AOA
        PDP
        CEC
        BAPC
        CODE
        TEAM
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("no solution", output.str());
}

TEST(TC, TC4)
{
    std::stringstream input(R"(
        2 2 10
        DELEVELEDB
        ATESTSETPC
        DELEVELED
        TESTSET
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("BAPC", output.str());
}

TEST(TC, TC5)
{
    std::stringstream input(R"(
        1 3 3
        ABC
        DEF
        GHI
        I
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("ABCDEFGH", output.str());
}

TEST(TC, TC6)
{
    std::stringstream input(R"(
        1 3 3
        ABC
        DEF
        GII
        I
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("ambiguous", output.str());
}

TEST(TC, TC7)
{
    std::stringstream input(R"(
        3 2 2
        AB
        CD
        A
        B
        CD
    )");
    std::stringstream output;

    run_test(input, output);

    EXPECT_EQ("empty solution", output.str());
}