#include <iostream>
#include <vector>
#include <bit>

namespace {

std::vector<int64_t> calc_divisors(int64_t val) {
    std::vector<int64_t> result;

    auto max_divisor = int64_t(1 << ((std::bit_width<uint64_t>(val) + 1) / 2));
    for (auto i = int64_t(2); i < max_divisor && i <= val; ++i)
    {
        if (val % i != 0) {
            continue;
        }

        result.push_back(i);

        while (val % i == 0) {
            val /= i;
        }
    }

    if (val != 1) {
        result.push_back(val);
    }

    return result;
}

template <typename _It>
int64_t count_coprime_under(int64_t max_val, int64_t base, _It begin, _It end)
{
    if (begin == end) {
        return max_val / base;
    }

    auto next = std::next(begin);

    auto not_use_last = count_coprime_under(max_val, base, next, end);
    auto use_last = count_coprime_under(max_val, -(*begin) * base, next, end);

    return not_use_last + use_last;
}

int64_t count_coprime_under(int64_t val, const std::vector<int64_t>& divisors)
{
    std::vector<int64_t> current(1 << divisors.size());
    current.clear();
    std::vector<int64_t> next(1 << divisors.size());
    next.clear();

    current.push_back(1);

    for (auto&& d : divisors)
    {
        for(auto&& v : current) {
            next.push_back(-v * d);
            next.push_back(v);
        }

        std::swap(current, next);
        next.clear();
    }

    int64_t total = 0;
    for (auto&& v : current) {
        total += (val / v);
    }

    return total;
}

}

int64_t solution(int64_t val)
{
    auto divisors = calc_divisors(val);

    //auto result = count_coprime_under(val, divisors);
    auto result = count_coprime_under(val, 1, divisors.begin(), divisors.end());

    return result;
}

#ifndef TEST_ENABLED
int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t val;
    std::cin >> val;

    std::cout << solution(val) << '\n';

    return 0;
}
#endif