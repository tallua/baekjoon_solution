#include <iostream>
#include <vector>
#include <limits>

using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> map;
    map.resize(N);
    for(auto& row : map)
        row.resize(M);

    for(int n = 0; n < N; ++n)
    {
        for(int m = 0; m < M; ++m)
        {
            cin >> map[n][m];
        }
    }

    vector<int> current_cost;
    vector<int> next_cost;

    current_cost.resize(M, 0);
    next_cost.resize(M, 0);

    for(int n = 0; n < N; ++n)
    {
        if(n == 0)
        {
            int sum = 0;
            for(int m = 0; m < M; ++m)
            {
                sum += map[n][m];
                next_cost[m] = sum;
            }
        }
        else
        {
            for(int m = 0; m < M; ++m)
            {
                int down = map[n][m] + current_cost[m];

                next_cost[m] = max(next_cost[m], down);

                int tmp_sum = down;
                for(int tmp = m - 1; tmp >= 0; --tmp)
                {
                    tmp_sum += map[n][tmp];
                    next_cost[tmp] = max(next_cost[tmp], tmp_sum);
                }

                tmp_sum = down;
                for(int tmp = m + 1; tmp < M; ++tmp)
                {
                    tmp_sum += map[n][tmp];
                    next_cost[tmp] = max(next_cost[tmp], tmp_sum);
                }
            }

        }

        current_cost = next_cost;
        for(int m = 0; m < M; ++m)
        {
            next_cost[m] = numeric_limits<int>::min();
        }
    }

    cout << current_cost[M - 1] << endl;

    return 0;
}