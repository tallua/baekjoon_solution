#include <gtest/gtest.h>

#include <array>
#include <iostream>
#include <vector>

using test_board_t = std::array<int, 36>;

extern bool solution(const test_board_t& board);

TEST(Test1917, tc1) {
    auto board =
        test_board_t{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                     0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    EXPECT_TRUE(solution(board));
}

TEST(Test1917, tc2) {
    test_board_t board = {
        0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    EXPECT_TRUE(solution(board));
}

TEST(Test1917, tc3) {
    test_board_t board = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    EXPECT_FALSE(solution(board));
}
