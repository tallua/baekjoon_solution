#include <gtest/gtest.h>
#include <vector>
#include <array>

extern std::size_t solution(const std::vector<std::array<long long, 3>>& sharks);

namespace {


TEST(Test1671, tc1) {
    EXPECT_EQ(2, solution({ 
        { 4, 5, 5 },
        { 10, 10, 8 },
        { 5, 7, 10 },
        { 8, 7, 7 },
        { 8, 10, 3},
    }));
}

TEST(Test1671, tc2) {
    EXPECT_EQ(1, solution({ 
        { 1, 2, 1 },
        { 4, 3, 5 },
        { 3, 1, 2 },
    }));
}

TEST(Test1671, tc3) {
    EXPECT_EQ(3, solution({ 
        { 1, 4, 2 },
        { 2, 3, 4 },
        { 3, 2, 1 },
        { 4, 1, 3 },
        { 100, 100, 100 },
    }));
}

TEST(Test1671, tc4) {
    EXPECT_EQ(1, solution({ 
        { 4, 3, 8 },
        { 4, 3, 8 },
        { 4, 3, 8 },
        { 4, 3, 8 },
    }));
}


TEST(Test1671, tc5) {
    EXPECT_EQ(1, solution({ 
        { 1, 1, 1 },
        { 4, 3, 8 },
        { 4, 3, 8 },
        { 4, 3, 8 },
        { 1, 1, 1 },
    }));
}

TEST(Test1671, tc6) {
    EXPECT_EQ(1, solution({ 
        { 1, 2, 3 },
        { 2, 3, 1 },
        { 3, 1, 2 },
        { 4, 4, 4 },
        { 4, 4, 4 },
        { 4, 4, 4 },
    }));
}

TEST(Test1671, tc7) {
    EXPECT_EQ(2, solution({ 
        { 1, 5, 9 },
        { 1, 5, 9 },
        { 9, 5, 1 },
    }));
}

TEST(Test1671, tc8) {
    EXPECT_EQ(1, solution({ 
        { 1, 5, 9 },
        { 1, 5, 9 },
        { 1, 6, 10 },
    }));
}

TEST(Test1671, tc9) {
    EXPECT_EQ(1, solution({ 
        { 1, 5, 9 },
    }));
}

TEST(Test1671, tc10) {
    std::vector<std::array<long long, 3>> sharks;

    for (auto i = (long long)(0); i < 50; ++i) {
        sharks.push_back({ i, i, i });
    }
    
    EXPECT_EQ(1, solution(sharks));
}

}