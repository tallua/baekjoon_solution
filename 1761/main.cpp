#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using dist_t = int;
using node_t = size_t;

const size_t LOOKUP_NONE = -1;

template <typename T>
void debug_vector(const std::vector<T>& vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << endl;
}

struct edge_t
{
    node_t node;
    dist_t distance;
};

struct euler_t
{
    node_t node;
    size_t height;

};

ostream& operator<<(ostream& os, const euler_t& euler)
{
    os << euler.node << '/' << euler.height;
    return os;
}

using tree_t = vector<vector<edge_t>>;
using euler_walk_t = vector<euler_t>;

void depth_traverse(const tree_t& tree, node_t node, size_t height,
                euler_walk_t& euler_walks,
                vector<size_t>& lookup, vector<dist_t>& depth)
{
    euler_walks.push_back({ node, height });

    for (size_t i = 0; i < tree[node].size(); ++i)
    {
        if (lookup[tree[node][i].node] == LOOKUP_NONE) {
            lookup[tree[node][i].node] = euler_walks.size();
            depth[tree[node][i].node] = depth[node] + tree[node][i].distance;
            depth_traverse(tree, tree[node][i].node, height + 1, euler_walks, lookup, depth);
            euler_walks.push_back({ node, height });
        }
    }
}


struct LcaDB
{
private:
    size_t N;
    vector<euler_t> data;

    const euler_t none_node = { 0, numeric_limits<size_t>::max() };

public:
    LcaDB(const euler_walk_t& walks)
        : N(walks.size())
    {
        data.resize(3 * N);
        _init(walks, 0, 0, N);
    }

    node_t query(node_t n1, node_t n2) const
    {
        size_t ql, qr;
        if (n1 < n2)
        {
            ql = n1;
            qr = n2 + 1;
        }
        else
        {
            ql = n2;
            qr = n1 + 1;
        }

        const auto& result = _query(0, 0, N, ql, qr);

        return result.node;
    }

private:
    void _init(const euler_walk_t& walks, size_t index, size_t begin, size_t end)
    {
        if (end - begin == 1)
        {
            data[index] = walks[begin];
            return;
        }

        size_t mid = (begin + end) / 2;

        _init(walks, 2 * index + 1, begin, mid);
        _init(walks, 2 * index + 2, mid, end);

        if (data[2 * index + 1].height < data[2 * index + 2].height)
            data[index] = data[2 * index + 1];
        else
            data[index] = data[2 * index + 2];
    }

    const euler_t& _query(size_t index, size_t begin, size_t end, size_t ql, size_t qr) const
    {
        if (end <= ql || qr <= begin)
            return none_node;
        //cout << begin << " " << end << " " << ql << " " << qr << '\n';
        if (ql <= begin && end <= qr)
            return data[index];

        size_t mid = (begin + end) / 2;

        const auto& left = _query(2 * index + 1, begin, mid, ql, qr);
        const auto& right = _query(2 * index + 2, mid, end, ql, qr);

        if (left.height < right.height)
            return left;
        else
            return right;
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    tree_t tree;
    tree.resize(N);
    for (size_t n = 0; n < N - 1; ++n)
    {
        node_t n1, n2;
        dist_t dist;
        cin >> n1 >> n2 >> dist;

        tree[n1 - 1].push_back({ n2 - 1, dist });
        tree[n2 - 1].push_back({ n1 - 1, dist });
    }

    // depth travers
    vector<size_t> lookup;
    vector<dist_t> depth;
    euler_walk_t euler_walks;
    lookup.resize(N, LOOKUP_NONE);
    depth.resize(N, 0);
    euler_walks.reserve(N * 2);

    lookup[0] = 0;
    depth[0] = 0;

    depth_traverse(tree, 0, 0, euler_walks, lookup, depth);
    //debug_vector(euler_walks);
    //debug_vector(lookup);
    //debug_vector(depth);

    // lca
    LcaDB lca_db(euler_walks);

    size_t M;
    cin >> M;

    for (size_t m = 0; m < M; ++m)
    {
        node_t n1, n2;
        cin >> n1 >> n2;

        const node_t lca = lca_db.query(lookup[n1 - 1], lookup[n2 - 1]);
        //cout << "lca : " << lca << '\n';
        const dist_t dist = (depth[n1 - 1] - depth[lca]) + (depth[n2 - 1] - depth[lca]);

        cout << dist << '\n';
    }

    return 0;
}
