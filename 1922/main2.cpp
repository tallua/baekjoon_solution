#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct link
{
    int node1, node2;
    int weight;
};

int find_group(vector<int> &group, int n)
{
    if (group[n] == n)
        return n;
        
    group[n] = find_group(group, group[n]);
    return group[n];
}

int kruskal(const int N, const vector<link> &edges)
{
    vector<int> group;
    group.resize(N);
    for (int n = 0; n < N; ++n)
    {
        group[n] = n;
    }

    int total_dist = 0;

    for (auto &l : edges)
    {
        int group1 = find_group(group, l.node1);
        int group2 = find_group(group, l.node2);
        if (group1 != group2)
        {
            // merge
            total_dist += l.weight;
            group[group1] = group2;
        }
    }

    return total_dist;
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<link> edges;
    for (int m = 0; m < M; ++m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        edges.push_back({.node1 = a, .node2 = b, .weight = c});
    }

    auto edge_cmp = [](const link &lhs, const link &rhs) { return lhs.weight < rhs.weight; };
    std::sort(edges.begin(), edges.end(), edge_cmp);

    int total_dist = kruskal(N, edges);

    cout << total_dist << '\n';

    return 0;
}
