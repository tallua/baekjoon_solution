#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<std::size_t>>;
using group_t = int;

template <typename _Fn>
void dfs_graph(graph_t const& graph, std::size_t index, const _Fn& func) noexcept {
    if (!func(index)) {
        return;
    }

    for (auto& link : graph[index]) {
        dfs_graph<_Fn>(graph, link, func);
    }
}

struct TarjanContext {
    TarjanContext(std::size_t n) : scc_group(1), stack(), on_stack(n, false) { stack.reserve(n); }

    group_t scc_group;
    std::vector<std::size_t> stack;
    std::vector<bool> on_stack;
};

group_t calcSCC(graph_t const& graph, std::size_t index, TarjanContext& tarjan, std::vector<group_t>& scc) {
    scc[index] = tarjan.scc_group++;
    tarjan.stack.push_back(index);
    tarjan.on_stack[index] = true;

    group_t min_node = scc[index];
    for (auto adj : graph[index]) {
        if (scc[adj] == 0)
            min_node = std::min(min_node, calcSCC(graph, adj, tarjan, scc));
        else if (tarjan.on_stack[adj])
            min_node = std::min(min_node, scc[adj]);
    }

    if (min_node == scc[index]) {
        while (index != tarjan.stack.back()) {
            size_t top = tarjan.stack.back();
            tarjan.stack.pop_back();
            tarjan.on_stack[top] = false;

            scc[top] = scc[index];
        }
        tarjan.stack.pop_back();
        tarjan.on_stack[index] = false;
    }

    return min_node;
}

auto calcSCC(graph_t const& graph) {
    std::vector<group_t> scc(graph.size(), 0);

    TarjanContext tarjan(graph.size());
    for (std::size_t i{0}; i < scc.size(); ++i) {
        if (scc[i] != 0) {
            continue;
        }

        calcSCC(graph, i, tarjan, scc);
    }

    return scc;
}

auto calcWinner(graph_t const& graph, std::size_t index) {
    std::vector<bool> result(graph.size(), false);
    dfs_graph(graph, index, [&](std::size_t index) {
        if (result[index]) {
            return false;
        }
        result[index] = true;
        return true;
    });
    return result;
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    while (std::cin >> n) {
        int m;
        std::cin >> m;

        const auto index_of = [n](int node) -> std::size_t { return 0 < node ? node - 1 : n - node - 1; };

        graph_t graph(2 * n);

        while (m--) {
            int a, b;
            std::cin >> a >> b;

            graph[index_of(-a)].push_back(index_of(b));
            graph[index_of(-b)].push_back(index_of(a));
        }
        graph[index_of(-1)].push_back(index_of(1));

        // check scc
        bool is_valid_scc = true;
        const auto scc = calcSCC(graph);
        for (int i{1}; i <= n; ++i) {
            if (scc[index_of(i)] == scc[index_of(-i)]) {
                is_valid_scc = false;
                break;
            }
        }

        if (is_valid_scc) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }

    return 0;
}