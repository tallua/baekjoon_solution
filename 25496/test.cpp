#include <gtest/gtest.h>
#include <vector>

extern int solution(int current, const std::vector<int>& costs);

namespace {


TEST(Test25946, tc1) {
    EXPECT_EQ(3, solution(190, { 20, 1, 8, 1, 10 }));
}

TEST(Test25946, tc2) {
    EXPECT_EQ(3, solution(195, { 20, 1, 8, 1 }));
}

TEST(Test25946, tc3) {
    EXPECT_EQ(5, solution(195, { 1, 1, 1, 1, 1 }));
}

TEST(Test25946, tc4) {
    EXPECT_EQ(5, solution(195, { 1, 1, 1, 1, 1, 1 }));
}

TEST(Test25946, tc5) {
    EXPECT_EQ(2, solution(195, { 2, 2 }));
}

}