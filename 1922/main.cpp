#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    struct link
    {
        int node, w;
    };

    vector<vector<link>> edges;
    edges.resize(N);
    for (int m = 0; m < M; ++m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        edges[a].push_back({.node = b, .w = c});
        edges[b].push_back({.node = a, .w = c});
    }

    auto pq_cmp = [](const link &lhs, const link &rhs) { return lhs.w > rhs.w; };
    priority_queue<link, vector<link>, decltype(pq_cmp)> pq(pq_cmp);

    int total_dist = 0;
    pq.push({.node = 0, .w = 0});

    vector<bool> visited;
    visited.resize(N, false);

    while(!pq.empty())
    {
        auto l = pq.top();
        pq.pop();

        if(visited[l.node])
            continue;
        visited[l.node] = true;
        total_dist += l.w;

        for(auto& next : edges[l.node])
        {
            if(visited[next.node])
                continue;

            pq.push(next);
        }
    }

    cout << total_dist << '\n';

    return 0;
}
