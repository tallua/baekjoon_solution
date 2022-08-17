#include <gtest/gtest.h>

extern int64_t solution(int64_t val);

namespace {

TEST(TEST_11689, TC1) { EXPECT_EQ(1, solution(1)); }

TEST(TEST_11689, TC2) { EXPECT_EQ(4, solution(5)); }

TEST(TEST_11689, TC3) { EXPECT_EQ(4, solution(10)); }

TEST(TEST_11689, TC4) { EXPECT_EQ(24, solution(45)); }

TEST(TEST_11689, TC5) { EXPECT_EQ(60, solution(99)); }

TEST(TEST_11689, TC6) { EXPECT_EQ(1, solution(2)); }

TEST(TEST_11689, TC7) { EXPECT_EQ(1021870080, solution(6469693230)); }

TEST(TEST_11689, TC8) { EXPECT_EQ(3741114816, solution(11223344556)); }

TEST(TEST_11689, TC9) { EXPECT_EQ(41152263000, solution(123456789012)); }

}  // namespace
