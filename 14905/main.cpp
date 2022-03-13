#include <array>
#include <cassert>
#include <iostream>
#include <vector>

auto calc_primes(std::size_t Len) {
    std::vector<bool> is_prime(Len, true);

    is_prime[0] = false;
    is_prime[1] = false;

    for (auto j = 4; j < Len; j += 2) {
        is_prime[j] = false;
    }

    for (auto i = std::size_t(3); i < Len; i += 2) {
        if (!is_prime[i]) {
            continue;
        }

        for (auto j = i * 2; j < Len; j += i) {
            is_prime[j] = false;
        }
    }

    return is_prime;
}

std::array<int, 4> run_test(int input) {
    const int margin = input / 20 + 20;
    switch (input % 4) {
        case 0: {
            auto is_prime = calc_primes(input / 4 + margin);
            for (auto i = input / 4; i < input / 4 + margin; ++i) {
                const auto other = (input / 2) - i;
                if (is_prime[i] && is_prime[other]) {
                    return {i, i, other, other};
                }
            }

            assert("require increase margin");
            return {0, 0, 0, 0};
        }
        case 2: {
            std::array<int, 4> result;

            auto is_prime = calc_primes(input / 4 + margin);
            for (auto i = input / 4; i < input / 4 + margin; ++i) {
                const auto other = (input / 2 - 1) - i;
                if (is_prime[i] && is_prime[other]) {
                    result[0] = i;
                    result[1] = other;
                    break;
                }
            }
            for (auto i = input / 4; i < input / 4 + margin; ++i) {
                const auto other = (input / 2 + 1) - i;
                if (is_prime[i] && is_prime[other]) {
                    result[2] = i;
                    result[3] = other;
                    break;
                }
            }

            assert("require increase margin");
            return result;
        }
        case 3:
        case 1: {
            auto is_prime = calc_primes(input / 3 + margin);
            for (auto i = input / 3 - 1; i < input / 3 + margin; ++i) {
                if (!is_prime[i]) {
                    continue;
                }

                for (auto j = input / 3 - 1; j < input / 3 + margin; ++j) {
                    if (!is_prime[j]) {
                        continue;
                    }

                    const auto other = input - 2 - i - j;
                    if (is_prime[other]) {
                        return {2, i, j, other};
                    }
                }
            }

            assert("require increase margin");
            return {0, 0, 0, 0};
        }
    }
    return {0, 0, 0, 0};
}

#ifndef TEST_ENABLED

int main(int argc, char** argv) {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int input;
    while (std::cin >> input) {
        if (input < 8) {
            std::cout << "Impossible.\n";
            continue;
        }

        const auto output = run_test(input);

        bool is_first_input = true;
        for (auto o : output) {
            if (is_first_input) {
                std::cout << o;
                is_first_input = false;
            } else {
                std::cout << ' ' << o;
            }
        }
        std::cout << '\n';
    }

    return 0;
}

#endif