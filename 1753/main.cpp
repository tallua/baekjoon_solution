#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, init;
    cin >> V >> E >> init;

    init--;

    // build graph
    struct link {
        int w;
        int node;
    };

    vector<vector<link>> edges;
    edges.resize(V);

    for(int e = 0; e < E; ++e)
    {
        int u, v, w;
        cin >> u >> v >> w;
        
        u--;
        v--;

        edges[u].push_back({ .w = w, .node = v });
        //edges[v].push_back({ .w = w, .node = u });
    }

    // dijkstra
    vector<int> min_dist;
    min_dist.resize(V, -1);

    auto pq_cmp = [](const link& lhs, const link& rhs){ return lhs.w > rhs.w; };
    priority_queue<link, std::vector<link>, decltype(pq_cmp)> pq(pq_cmp);

    pq.push({ .w = 0, .node = init});

    while(pq.size() != 0)
    {
        link l = pq.top();
        pq.pop();

        if(min_dist[l.node] != -1)
            continue;
        min_dist[l.node] = l.w;

        for(auto& other : edges[l.node])
        {
            if(min_dist[other.node] != -1)
                continue;

            pq.push({ .w = other.w + min_dist[l.node], .node = other.node});
        }
    }

    for(auto& dist : min_dist)
    {
        if(dist == -1)
            cout << "INF\n";
        else
            cout << dist << '\n';
    }


    return 0;
}