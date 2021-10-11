#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

using node_t = std::size_t;
using graph_t = vector<vector<node_t>>;

struct context
{
    node_t next_id;
    vector<node_t> min_reachable;

    context(std::size_t N)
        : next_id(0)
        , min_reachable(N, 0)
    {
    }
};

using edge_t = std::pair<node_t, node_t>;


node_t
dfs(const graph_t& graph, vector<edge_t>& articul_bridges, context& ctx, node_t node, node_t parent)
{
    ctx.min_reachable[node] = ++ctx.next_id;
    const node_t node_id = ctx.min_reachable[node];
    node_t min_reach = ctx.min_reachable[node];

    for (auto adj : graph[node]) {
        if (adj == parent) {
            continue;
        }

        if (ctx.min_reachable[adj] == 0) {
            const node_t min_child_reach = dfs(graph, articul_bridges, ctx, adj, node);
            const bool is_articul_bridge = min_child_reach > node_id;
            if (is_articul_bridge) {
                articul_bridges.push_back({ min(node, adj), max(node, adj) });
            }
            min_reach = min(min_reach, min_child_reach);
        }
        else {
            min_reach = min(min_reach, ctx.min_reachable[adj]);
        }
    }

    return min_reach;
}

std::vector<edge_t>
dfs(const graph_t& graph)
{
    std::vector<edge_t> articul_bridges;
    context ctx(graph.size());

    dfs(graph, articul_bridges, ctx, 1, 1);

    return articul_bridges;
}

#include <iostream>

int
main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t node_count, edge_count;
    cin >> node_count >> edge_count;

    graph_t graph(node_count + 1);
    for (size_t i = 0; i < edge_count; ++i) {
        node_t n1, n2;
        cin >> n1 >> n2;

        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    vector<edge_t> articul_bridges = dfs(graph);
    std::sort(articul_bridges.begin(), articul_bridges.end());

    std::cout << articul_bridges.size() << '\n';
    std::for_each(articul_bridges.begin(), articul_bridges.end(), [](const auto& bridge) {
        std::cout << (bridge.first) << ' ' << (bridge.second) << '\n';
    });

    return 0;
}