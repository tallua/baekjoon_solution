#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <iostream>

auto invert_bit(auto v) { return std::bit_ceil(v + 1) - v - 1; }

auto overflow_length(auto v) { return v - invert_bit(v); }

auto dfs(const auto& remains, auto bits, auto current) {
    if (std::popcount(bits) == 0) {
        const auto overflows = std::to_array(
            {overflow_length(current[0]), overflow_length(current[1])});

        return overflows[0] <= remains[0] && overflows[1] <= remains[1];
    }

    const auto lsb = std::bit_floor(bits);

    if (dfs(remains, bits - lsb,
            std::to_array({current[0] + lsb, current[1]}))) {
        return true;
    }

    if (dfs(remains, bits - lsb,
            std::to_array({current[0], current[1] + lsb}))) {
        return true;
    }

    return false;
}

void run_test(std::istream& is, std::ostream& os) {
    unsigned int N, A, B;
    is >> N >> A >> B;

    const auto left = std::min(A, B);
    const auto right = std::max(A, B);
    const auto distance = right - left;

    if (distance % 2 != 0) {
        os << "-1";
        return;
    }

    const auto half = distance / 2;
    const auto required = std::bit_ceil(half + 1) - half - 1;

    if (dfs(std::to_array({left - 1, N - right}), required,
            std::to_array({decltype(required)(0), decltype(required)(0)}))) {
        os << std::bit_width(half);
        return;
    }

    os << "-1";
    return;
}

#ifndef TEST_DISABLED

int main(int argc, char** argv) {
    run_test(std::cin, std::cout);

    return 0;
}

#endif