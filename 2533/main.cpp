#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int root = 0;
const int NULL_ID = numeric_limits<int>::max();

template <typename _T>
_T mymax(const _T &lhs, const _T &rhs) { return lhs < rhs ? rhs : lhs; }
template <typename _T>
_T mymin(const _T &lhs, const _T &rhs) { return lhs < rhs ? lhs : rhs; }

void build_tree(const vector<vector<int>> &edges, int root,
                vector<int> &parents, vector<int> &topology)
{
    const int N = parents.size();

    topology.push_back(root);
    parents[root] = root;

    int task_index = 0;
    while (task_index < N)
    {
        const int current_node = topology[task_index++];

        for (const int &linked_node : edges[current_node])
        {
            if (linked_node != parents[current_node])
            {
                parents[linked_node] = current_node;
                topology.push_back(linked_node);
            }
        }
    }
}


int count_early_adapter(const vector<vector<int>> &edges,
                          const vector<int> &parents, const vector<int> &topology)
{
    const int N = edges.size();
    vector<int> if_early;
    vector<int> if_lazy;
    if_early.resize(N, 0);
    if_lazy.resize(N, 1);

    for (auto t_rit = topology.rbegin(); t_rit != topology.rend(); ++t_rit)
    {
        const int current_node = *t_rit;
        const int parent_node = parents[current_node];
        if(current_node != root)
        {
            if_early[parent_node] += if_lazy[current_node];
            if_lazy[parent_node] += mymin(if_early[current_node], if_lazy[current_node]);
        }
    }

    //for (int i = 0; i < N; ++i)
    //{
    //    cout << if_early[i] << ' ';
    //}
    //cout << endl;
    //for (int i = 0; i < N; ++i)
    //{
    //    cout << if_lazy[i] << ' ';
    //}
    //cout << endl;

    return mymin(if_early[root], if_lazy[root]);
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<vector<int>> edges;
    edges.resize(N);
    for (int n = 0; n < N - 1; ++n)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    vector<int> parents;
    parents.resize(N, NULL_ID);
    vector<int> topology;
    topology.reserve(N);

    build_tree(edges, root, parents, topology);

    int early_adapter_count = count_early_adapter(edges, parents, topology);

    cout << early_adapter_count << '\n';

    return 0;
}
