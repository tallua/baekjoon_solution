#include <iostream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

bool bipartite(const vector<vector<size_t>>& owners, vector<size_t>& resource, vector<bool>& visited, size_t current)
{
    for(const auto& res : owners[current])
    {
        if(!visited[res])
        {
            visited[res] = true;
            
            if(resource[res] == numeric_limits<size_t>::max() ||
                bipartite(owners, resource, visited, resource[res]))
            {
                resource[res] = current;
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    vector<vector<size_t>> owners;
    owners.resize(N);
    for(size_t n = 0; n < N; ++n)
    {
        int K;
        cin >> K;

        for(int k = 0; k < K; ++k)
        {
            size_t tmp;
            cin >> tmp;

            owners[n].push_back(tmp - 1);
        }
    }

    vector<size_t> resource;
    resource.resize(M, numeric_limits<size_t>::max());

    size_t count = 0;
    for(size_t n = 0; n < N; ++n)
    {
        vector<bool> visited;
        visited.resize(M, false);

        if(bipartite(owners, resource, visited, n))
            count++;
    }

    cout << count << '\n';

    return 0;
}

