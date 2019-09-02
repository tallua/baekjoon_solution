#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using count_t = long long;
using cost_t = vector<vector<count_t>>;

count_t calc(const vector<pair<int, int>>& matrixes)
{
    size_t N = matrixes.size();

    cost_t costs;
    costs.resize(N);
    for(size_t i = 0; i < N; ++i)
    {
        costs[i].resize(N, 0);
    }


    // dist <- [0, N-1]
    for(size_t dist = 1; dist < N; ++dist)
    {
        // start <- [0, N - 1 - dist]
        for(size_t start = 0; start < N - dist; ++start)
        {
            size_t end = start + dist;

            count_t min = numeric_limits<count_t>::max();
            for(size_t mid = start; mid < end; ++mid)
            {
                count_t cost = costs[start][mid] + costs[mid + 1][end];
                cost += matrixes[start].first * matrixes[mid].second * matrixes[end].second;
                
                if(cost < min)
                    min = cost;
            }

            costs[start][end] = min;
            costs[end][start] = min;
        }
    }

    return costs[0][N - 1];
}

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    vector<pair<int, int>> matrixes;
    matrixes.resize(N);

    for(int n = 0; n < N; ++n)
    {
        cin >> matrixes[n].first >> matrixes[n].second;
    }

    cout << calc(matrixes) << '\n';

    return 0;
}






