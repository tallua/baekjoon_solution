#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <numeric>

extern std::array<int, 4> run_test(int input);


TEST(TC, TC1)
{
    auto result = run_test(24);
    EXPECT_EQ(24, std::accumulate(result.begin(), result.end(), 0));
}

TEST(TC, TC2)
{
    auto result = run_test(36);
    EXPECT_EQ(36, std::accumulate(result.begin(), result.end(), 0));
}

TEST(TC, TC3)
{
    auto result = run_test(46);
    EXPECT_EQ(46, std::accumulate(result.begin(), result.end(), 0));
}

TEST(TC, TC4)
{
    auto result = run_test(4107);
    EXPECT_EQ(4107, std::accumulate(result.begin(), result.end(), 0));
}

TEST(TC, TC_10000)
{
    for (auto i = std::size_t(8); i < 10000; ++i) {
        auto result = run_test(i);
        EXPECT_EQ(i, std::accumulate(result.begin(), result.end(), 0));
    }
}

TEST(TC, TC_MAX_1)
{
    auto result = run_test(99999998);
    EXPECT_EQ(99999998, std::accumulate(result.begin(), result.end(), 0));
}

TEST(TC, TC_MAX_2)
{
    auto result = run_test(99999999);
    EXPECT_EQ(99999999, std::accumulate(result.begin(), result.end(), 0));
}

TEST(TC, TC_MAX_3)
{
    auto result = run_test(100000000);
    EXPECT_EQ(100000000, std::accumulate(result.begin(), result.end(), 0));
}








template <std::size_t _Len>
constexpr auto calc_primes() {
    std::vector<bool> is_prime(_Len, true);

    for (auto i = std::size_t(2); i < _Len; ++i) {
        if (!is_prime[i]) {
            continue;
        }

        for (auto j = i * 2; j < _Len; j += i) {
            is_prime[j] = false;
        }
    }

    return is_prime;
}


TEST(UTIL, is_even_numbers_are_sum_of_prime)
{
    const auto is_prime = calc_primes<10000>();
    const auto is_sum_of_prime = [&] {
        std::vector<bool> sum_of_prime(10000, false);

        for (auto i = std::size_t(2); i < 10000; ++i) {
            if (!is_prime[i]) {
                continue;
            }

            for (auto j = i; j < 10000; ++j) {
                if (!is_prime[j]) {
                    continue;
                }

                if (10000 <= i + j) {
                    continue;
                }

                sum_of_prime[i + j] = true;
            }
        }

        return sum_of_prime;
    } ();

    for (auto i = std::size_t(4); i < 10000; i += 2) {
        EXPECT_TRUE(is_sum_of_prime[i]);
    }
}


