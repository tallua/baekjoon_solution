#include <iostream>

namespace {

auto ceil(auto lower_bound, auto base) {
    const auto diviend = lower_bound / base;
    return base * (lower_bound % base == 0 ? diviend : diviend + 1);
}

auto ceil(auto total, auto used, auto base) {
    return used + ceil(total - used, base);
}

}  // namespace

int solution(int D, int P, int Q) {
    const int64_t total = D, cost_0 = std::max(P, Q), cost_1 = std::min(P, Q);
    const auto lcm = cost_0 * cost_1;

    auto min_val = ((total / cost_0) + 1) * cost_0;

    if (cost_1 % cost_0 != 0) {
        for (auto i = int64_t(); i <= lcm / cost_0 && total > cost_0 * i; ++i) {
            min_val = std::min(min_val, ceil(total, cost_0 * i, cost_1));
            if (total < cost_0 * i + cost_1) {
                break;
            }
        }
    }

    const auto base = (total / lcm) * lcm;
    const auto total_remain = total % (cost_0 * cost_1);

    for (auto coef_0 = int64_t(); min_val != total_remain && coef_0 < cost_1;
         ++coef_0) {
        if (total_remain < cost_0 * coef_0) {
            min_val = std::min(min_val, base + cost_0 * coef_0);
            break;
        }

        min_val = std::min(min_val,
                           base + ceil(total_remain, cost_0 * coef_0, cost_1));
    }

    return min_val;
}

#ifndef TEST_ENABLED
int main(int argc, char** argv) {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int D, P, Q;
    std::cin >> D >> P >> Q;

    std::cout << solution(D, P, Q) << std::endl;

    return 0;
}
#endif