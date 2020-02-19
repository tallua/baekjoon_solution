#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const size_t none_id = numeric_limits<size_t>::max();

size_t call_count = 0;

bool bipartite_match(const vector<pair<size_t, size_t>> &graph, size_t id, vector<size_t> &assigned, vector<bool> &visited)
{
    call_count++;

    for (size_t avail = graph[id].first; avail < graph[id].second; ++avail)
    {
        if (!visited[avail])
        {
            visited[avail] = true;

            if (assigned[avail] == none_id || bipartite_match(graph, assigned[avail], assigned, visited))
            {
                assigned[avail] = id;
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--)
    {
        call_count = 0;

        size_t N, M;
        cin >> N >> M;

        vector<pair<size_t, size_t>> graph;
        graph.resize(N);
        for (size_t n = 0; n < N; ++n)
        {
            size_t a, b;
            cin >> a >> b;
            a--;

            graph[n] = { a, b };
        }

        vector<size_t> assigned;
        assigned.resize(M, none_id);

        size_t count = 0;
        for (size_t n = 0; n < N; ++n)
        {
            vector<bool> visited;
            visited.resize(M, false);

            if (bipartite_match(graph, n, assigned, visited))
                count++;
        }

        cout << "call : " << call_count << '\n';
        cout << count << '\n';
    }

    cout << endl;

    return 0;
}