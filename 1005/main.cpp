#include <iostream>
#include <vector>

using namespace std;

void solve(const vector<vector<int>>& graph, const vector<int>& cost, vector<int>& cache, int target)
{
    if(cache[target] != -1)
        return;

    int max_cost = 0;
    for(auto& precede : graph[target])
    {
        solve(graph, cost, cache, precede);
        max_cost = std::max(max_cost, cache[precede]);
    }

    max_cost += cost[target];

    cache[target] = max_cost;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--)
    {
        int N, K;
        cin >> N >> K;

        vector<int> cost;
        cost.resize(N);
        vector<vector<int>> graph;
        graph.resize(N);

        for(int n = 0; n < N; ++n)
        {
            cin >> cost[n];
        }

        for(int k = 0; k < K; ++k)
        {
            int a, b;
            cin >> a >> b;
            a--; b--;

            graph[b].push_back(a);
        }

        int W;
        cin >> W;
        
        vector<int> cache;
        cache.resize(N, -1);

        solve(graph, cost, cache, W - 1);

        cout << cache[W - 1] << '\n';
    }
    
    return 0;
}