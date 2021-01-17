#include <iostream>
#include <vector>
#include <map>

using namespace std;
using node_t = uint32_t;
using count_t = uint32_t;
using cost_t = uint64_t;

struct Edge
{
    node_t node;
    cost_t cost;
};

using Tree = vector<vector<Edge>>;

count_t calc_nodes(Tree& tree, vector<count_t>& cost_counts, node_t parent, node_t current)
{
    count_t sum_edge_cost = 0;
    for (auto& edge : tree[current])
    {
        if (edge.node == parent)
            continue;

        count_t edge_cost = calc_nodes(tree, cost_counts, current, edge.node);
        edge.cost = edge_cost;
        cost_counts[edge_cost]++;
        sum_edge_cost += edge_cost;
    }

    return sum_edge_cost + 1;
}

struct SegTree
{
    const size_t N;
    SegTree(const vector<count_t>& cost_counts)
        : N(cost_counts.size()), data(cost_counts.size() * 4)
    {
        build_data(cost_counts, 0, 0, N);
    }
private:

public:
    void inc(cost_t cost)
    {
        update(0, cost, 0, N, [cost](Data& d) { d.total += cost; d.count++; });
    }

    void dec(cost_t cost)
    {
        update(0, cost, 0, N, [cost](Data& d) { d.total -= cost; d.count--; });
    }

    cost_t query(count_t bridge_count) const
    {
        cost_t total = data[0].total;
        cost_t top_n = sum_of_top(0, 0, N, bridge_count);
        return total * 2 - top_n;
    }

private:
    struct Data
    {
        cost_t total;
        count_t count;

        Data operator + (const Data& other)
        {
            return { total + other.total, count + other.count };
        }
    };

    vector<Data> data;
    void build_data(const vector<count_t>& counts, size_t index, cost_t l, cost_t r)
    {
        if (r - 1 <= l)
        {
            data[index] = { l * cost_t(counts[l]), counts[l] };
            return;
        }

        size_t mid = (l + r) / 2;
        build_data(counts, index * 2 + 1, l, mid);
        build_data(counts, index * 2 + 2, mid, r);
        data[index] = data[index * 2 + 1] + data[index * 2 + 2];
    }

    template <typename T>
    void update(size_t index, cost_t target, cost_t l, cost_t r, const T& updater)
    {
        if (r - 1 <= l)
        {
            updater(data[index]);
            return;
        }

        cost_t mid = (l + r) / 2;
        if (target < mid)
            update(index * 2 + 1, target, l, mid, updater);
        else
            update(index * 2 + 2, target, mid, r, updater);

        data[index] = data[index * 2 + 1] + data[index * 2 + 2];
    }

    cost_t sum_of_top(size_t index, cost_t l, cost_t r, count_t bridge_count) const
    {
        if (r - 1 <= l)
        {
            return l * cost_t(bridge_count);
        }

        if (data[index].count <= bridge_count)
        {
            return data[index].total;
        }

        cost_t mid = (l + r) / 2;
        count_t right_count = data[index * 2 + 2].count;

        if (right_count < bridge_count)
        {
            return sum_of_top(index * 2 + 2, mid, r, right_count) +
                sum_of_top(index * 2 + 1, l, mid, bridge_count - right_count);
        }
        else
        {
            return sum_of_top(index * 2 + 2, mid, r, bridge_count);
        }
    }
};

struct Query
{
    count_t bridge_count;
    cost_t& result;
};

using QueryLists = vector<vector<Query>>;

struct Context
{
    SegTree segtree;
    QueryLists queries;
};

void dfs(const Tree& tree, Context& context, node_t parent, node_t node)
{
    for (auto& query : context.queries[node])
    {
        query.result = context.segtree.query(query.bridge_count);
    }

    for (const auto& edge : tree[node])
    {
        if (parent == edge.node)
            continue;

        context.segtree.dec(edge.cost);
        context.segtree.inc(tree.size() - edge.cost);
        dfs(tree, context, node, edge.node);
        context.segtree.dec(tree.size() - edge.cost);
        context.segtree.inc(edge.cost);
    }
}

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N, Q;
    cin >> N >> Q;

    const node_t root_node = 0;
    Tree tree(N);
    for (size_t n = 0; n < N - 1; ++n)
    {
        uint32_t u, v;
        cin >> u >> v;

        tree[u - 1].push_back({ v - 1, 0 });
        tree[v - 1].push_back({ u - 1, 0 });
    }

    vector<count_t> cost_counts(N);
    calc_nodes(tree, cost_counts, root_node, root_node);

    Context context = { SegTree(cost_counts), QueryLists(N) };

    // vulnerable here for context referencing query_results directly.
    vector<cost_t> query_results(Q);
    for (size_t q = 0; q < Q; ++q)
    {
        node_t root;
        count_t bridge_count;
        cin >> root >> bridge_count;

        context.queries[root - 1].push_back({ bridge_count, query_results[q] });
    }

    dfs(tree, context, root_node, root_node);

    for (const auto& query_result : query_results)
    {
        cout << query_result << '\n';
    }

    return 0;
}