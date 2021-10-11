#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

using node_t = size_t;
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


void
dfs(const graph_t& graph, vector<bool>& is_articul, context& ctx, node_t node, node_t parent)
{
    ctx.min_reachable[node] = ++ctx.next_id;

    node_t min_reach = ctx.min_reachable[node];

    for (auto adj : graph[node]) {
        if (adj == parent) {
            continue;
        }

        if (ctx.min_reachable[adj] == 0) {
            dfs(graph, is_articul, ctx, adj, node);
            const bool is_articul_bridge = ctx.min_reachable[adj] >= ctx.min_reachable[node];
            if (is_articul_bridge) {
                is_articul[node] = true;
            }
        }
        min_reach = min(min_reach, ctx.min_reachable[adj]);
    }

    ctx.min_reachable[node] = min_reach;
}

void
dfs(const graph_t& graph, vector<bool>& is_articul)
{
    context ctx(graph.size());

    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (ctx.min_reachable[i] == 0) {
            ctx.min_reachable[i] = ++ctx.next_id;

            std::size_t articul_child_cnt = 0;

            for (auto adj : graph[i]) {
                if (ctx.min_reachable[adj] != 0) {
                    continue;
                }

                dfs(graph, is_articul, ctx, adj, i);
                articul_child_cnt++;
            }

            if (articul_child_cnt >= 2) {
                is_articul[i] = true;
            }
        }
    }
}

#include <iostream>

int
main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t node_count, edge_count;
    cin >> node_count >> edge_count;

    graph_t graph(node_count);
    for (size_t i = 0; i < edge_count; ++i) {
        node_t n1, n2;
        cin >> n1 >> n2;

        graph[n1 - 1].push_back(n2 - 1);
        graph[n2 - 1].push_back(n1 - 1);
    }

    vector<bool> is_articulation(node_count, false);
    dfs(graph, is_articulation);

    std::cout << std::count(is_articulation.begin(), is_articulation.end(), true) << '\n';
    bool is_first = true;
    for (std::size_t i = 0; i < node_count; ++i) {
        if (is_articulation[i]) {
            if (!is_first) {
                std::cout << ' ';
            }
            std::cout << (i + 1);
            is_first = false;
        }
    }

    return 0;
}