#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

namespace {

using Stat = std::array<long long, 3>;
bool can_eat(const Stat& lhs, const Stat& rhs) noexcept {
    return lhs[0] >= rhs[0] && lhs[1] >= rhs[1] && lhs[2] >= rhs[2];
}

using Graph = std::vector<std::vector<int>>;
Graph make_graph(std::size_t node_count) {
    return Graph(node_count, std::vector<int>(node_count));
}

bool dfs(const Graph& max_flow, const Graph& current_flow, const std::size_t e,
         std::vector<std::size_t>& p, std::vector<bool>& visited) {
    const auto current = p.back();
    if (current == e) {
        return true;
    }

    for (auto i = std::size_t(); i < max_flow.size(); ++i) {
        if (!visited[i] && max_flow[current][i] - current_flow[current][i] > 0) {
            visited[i] = true;
            p.push_back(i);

            if (dfs(max_flow, current_flow, e, p, visited)) {
                return true;
            }

            p.pop_back();
        }
    }

    return false;
}

std::vector<std::size_t> find_path(const Graph& max_flow,
                                   const Graph& current_flow, std::size_t s,
                                   std::size_t e) {
    std::vector<std::size_t> path;
    path.push_back(s);

    std::vector<bool> visited(max_flow.size(), false);
    visited[s] = true;

    if (!dfs(max_flow, current_flow, e, path, visited)) {
        return {};
    }

    return path;
}

std::size_t maximum_matching(const Graph& max_flow, std::size_t s,
                             std::size_t e) {
    auto current_flow = make_graph(max_flow.size());

    while (true) {
        auto path = find_path(max_flow, current_flow, s, e);

        if (path.empty()) {
            break;
        }

        auto flow = std::numeric_limits<int>::max();
        for (auto i = std::size_t(); i < path.size() - 1; ++i) {
            flow = std::min(flow, max_flow[path[i]][path[i + 1]] -
                                      current_flow[path[i]][path[i + 1]]);
        }

        for (auto i = std::size_t(); i < path.size() - 1; ++i) {
            current_flow[path[i]][path[i + 1]] += flow;
            current_flow[path[i + 1]][path[i]] -= flow;
        }
    };

    const auto result = std::accumulate(current_flow[0].begin(), current_flow[0].end(), 0);

    return static_cast<std::size_t>(result);
}

}  // namespace

std::size_t solution(const std::vector<std::array<long long, 3>>& sharks) {
    auto max_flow = make_graph(2 * sharks.size() + 2);
    for (auto i = std::size_t(); i < sharks.size(); ++i) {
        max_flow[0][2 * i + 1] = 2;
        max_flow[2 * i + 2][2 * sharks.size() + 1] = 1;
    }

    for (auto i = std::size_t(); i < sharks.size(); ++i) {
        const auto node_index = 2 * i + 1;
        if (max_flow[0][2 * i + 1] == 0) {
            continue;
        }

        for (auto j = i + 1; j < sharks.size(); ++j) {
            const bool i_eat_j = can_eat(sharks[i], sharks[j]);
            const bool j_eat_i = can_eat(sharks[j], sharks[i]);

            if (i_eat_j && j_eat_i) {
                max_flow[0][2 * i + 1] += 2;
                max_flow[0][2 * j + 1] = 0;
                max_flow[2 * i + 1][2 * j + 2] = 1;
            } else if (i_eat_j) {
                max_flow[2 * i + 1][2 * j + 2] = 1;
            } else if (j_eat_i) {
                max_flow[2 * j + 1][2 * i + 2] = 1;
            }
        }
    }

    const auto edge_count =
        maximum_matching(max_flow, 0, 2 * sharks.size() + 1);

    return sharks.size() - edge_count;
}

#ifndef TEST_ENABLED

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::cin >> n;

    std::vector<std::array<long long, 3>> sharks(n);
    for (auto i = std::size_t(); i < n; ++i) {
        std::cin >> sharks[i][0] >> sharks[i][1] >> sharks[i][2];
    }

    std::cout << solution(sharks) << '\n';

    return 0;
}
#endif
