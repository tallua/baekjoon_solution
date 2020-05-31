#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
const size_t ID_END = numeric_limits<size_t>::max();

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

void build_scc2(const vector<vector<size_t>>& rev_graphs, vector<size_t>& result, size_t index, size_t id)
{
    if(result[index] != ID_END)
        return;
    result[index] = id;

    for(size_t i = 0; i < rev_graphs[index].size(); ++i)
    {
        build_scc2(rev_graphs, result, rev_graphs[index][i], id);
    }
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t V, E;
    cin >> V >> E;

    // parse input
    vector<vector<size_t>> graphs;
    graphs.resize(V + 1);
    vector<vector<size_t>> rev_graphs;
    rev_graphs.resize(V + 1);
    for(size_t e = 0; e < E; ++e)
    {
        size_t from, to;
        cin >> from >> to;
        graphs[from].push_back(to);
        rev_graphs[to].push_back(from);
    }

    // forward
    vector<bool> visited;
    visited.resize(V + 1, false);
    vector<size_t> topology;
    topology.reserve(V);

    for(size_t v = 1; v <= V; ++v)
    {
        topology_sort(graphs, v, visited, topology);
    }

    // backward
    size_t scc_count = 0;
    vector<size_t> scc;
    scc.resize(V + 1, ID_END);
    
    for(size_t v = V; v-- > 0;)
    {
        size_t current = topology[v];
        size_t current_scc = scc[topology[v]];
        if(scc[topology[v]] == ID_END)
        {
            build_scc2(rev_graphs, scc, topology[v], scc_count++);
        }
    }

    // parse result
    size_t idmap_cnt = 0;
    vector<size_t> idmap;
    idmap.resize(scc_count, ID_END);

    vector<vector<size_t>> result;
    result.resize(scc_count);
    for(size_t v = 1; v <= V; ++v)
    {
        if(idmap[scc[v]] == ID_END)
        {
            idmap[scc[v]] = idmap_cnt++;
        }

        result[idmap[scc[v]]].push_back(v);
    }

    // output
    cout << scc_count << '\n';
    for(size_t i = 0; i < result.size(); ++i)
    {
        for(size_t j = 0; j < result[i].size(); ++j)
        {
            cout << result[i][j] << ' ';
        }
        
        cout << "-1\n";
    }

    cout << endl;

    return 0;
}