#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const size_t none_id = numeric_limits<size_t>::max();

bool bipartite_match(const vector<vector<size_t>>& graph, size_t id, vector<size_t>& assigned, vector<bool>& visited)
{
    for(const size_t& avail : graph[id])
    {
        if(!visited[avail])
        {
            visited[avail] = true;

            if(assigned[avail] == none_id || bipartite_match(graph, assigned[avail], assigned, visited))
            {
                assigned[avail] = id;
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N, M;
    cin >> N >> M;

    vector<vector<size_t>> graph;
    graph.resize(N);
    for(size_t m = 0; m < M; ++m)
    {
        size_t a, b;
        cin >> a >> b;
        a--; b--;

        graph[a].push_back(b);
    }

    for(size_t n = 0; n < N; ++n)
    {
        sort(graph[n].begin(), graph[n].end());
    }

    vector<size_t> assigned;
    assigned.resize(N, none_id);

    size_t count = 0;
    for(size_t n = 0; n < N; ++n)
    {
        vector<bool> visited;
        visited.resize(N, false);

        if(bipartite_match(graph, n, assigned, visited))
            count++;
    }

    cout << count << endl;

    return 0;
}