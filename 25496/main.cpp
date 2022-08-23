#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

namespace {

constexpr auto max_cost = 200;

}

int solution(int current, const std::vector<int>& costs)
{
    std::array<decltype(current), max_cost + 1> cost_counts = { 0, };
    std::for_each(costs.begin(), costs.end(), [&](auto cost) {
        cost_counts[cost]++;
    });

    auto remain_stamina = max_cost - current;
    auto accessary_count = 0;

    auto cost_it = cost_counts.begin();
    for (; cost_it != cost_counts.end(); ++cost_it) {
        if (*cost_it == 0) {
            continue;
        }

        const auto stamina = decltype(remain_stamina)(std::distance(cost_counts.begin(), cost_it));

        const auto max_count = (remain_stamina / stamina) + (remain_stamina % stamina == 0 ? 0 : 1);
        const auto added_count = std::min(max_count, *cost_it);
        const auto used_stamina = added_count * stamina;

        accessary_count += added_count;
        remain_stamina -= used_stamina;

        if (remain_stamina < 0) {
            break;
        }
    }

    return accessary_count;
}

#ifndef TEST_ENABLED
int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int p, n;
    std::cin >> p >> n;

    std::vector<int> a(n);
    for (auto i = int(); i < n; ++i) {
        std::cin >> a[i];
    }

    std::cout << solution(p, a) << '\n';

    return 0;
}
#endif
