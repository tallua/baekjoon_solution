#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// dfs, post order
void topology_sort(const vector<vector<size_t>>& graph, size_t index, vector<bool>& visited, vector<size_t>& result)
{
    if(visited[index])
        return;
    visited[index] = true;

    for(size_t i = 0; i < graph[index].size(); ++i)
    {
        topology_sort(graph, graph[index][i], visited, result);
    }

    result.push_back(index);
}

void build_scc(const vector<vector<size_t>>& rev_graphs, vector<bool>& visited, size_t index, vector<size_t>& result)
{
    if(visited[index])
        return;
    visited[index] = true;
    result.push_back(index);

    for(size_t i = 0; i < rev_graphs[index].size(); ++i)
    {
        build_scc(rev_graphs, visited, rev_graphs[index][i], result);
    }
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t V, E;
    cin >> V >> E;

    vector<vector<size_t>> graphs;
    graphs.resize(V);
    vector<vector<size_t>> rev_graphs;
    rev_graphs.resize(V);
    for(size_t e = 0; e < E; ++e)
    {
        size_t from, to;
        cin >> from >> to;
        graphs[from - 1].push_back(to - 1);
        rev_graphs[to - 1].push_back(from - 1);
    }

    vector<bool> visited;
    visited.resize(V, false);
    vector<size_t> topology;
    topology.reserve(V);

    for(size_t v = 0; v < V; ++v)
    {
        topology_sort(graphs, v, visited, topology);
    }

    fill(visited.begin(), visited.end(), false);

    vector<vector<size_t>> result;
    size_t v = V;
    do
    {
        v--;
        if(!visited[topology[v]])
        {
            result.emplace_back();
            build_scc(rev_graphs, visited, topology[v], result.back());
        }

    } while(v != 0);

    for(size_t v = 0; v < result.size(); ++v)
    {
        sort(result[v].begin(), result[v].end());
    }

    sort(result.begin(), result.end(), [](const auto& lhs, const auto& rhs) {
        if(lhs.size() == 0)
            return false;
        if(rhs.size() == 0)
            return true;
        return lhs[0] < rhs[0];
    });

    cout << result.size() << '\n';
    for(size_t v = 0; v < result.size(); ++v)
    {
        for(size_t i = 0; i < result[v].size(); ++i)
        {
            cout << (result[v][i] + 1) << ' ';
        }
        cout << "-1\n";
    }
    cout << endl;

    return 0;
}