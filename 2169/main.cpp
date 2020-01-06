#include <iostream>
#include <vector>
#include <deque>
#include <limits>

using namespace std;

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> map;
    map.resize(N);
    for (auto &row : map)
        row.resize(M);

    for (int n = 0; n < N; ++n)
    {
        for (int m = 0; m < M; ++m)
        {
            cin >> map[n][m];
        }
    }

    vector<int> current_costs;
    current_costs.resize(M);

    current_costs[0] = map[0][0];
    for (int m = 1; m < M; ++m)
        current_costs[m] = current_costs[m - 1] + map[0][m];

    for (int n = 1; n < N; ++n)
    {
        vector<int> to_right;
        vector<int> to_left;
        to_right.resize(M, numeric_limits<int>::min());
        to_left.resize(M, numeric_limits<int>::min());

        to_right[0] = current_costs[0] + map[n][0];
        for (int m = 1; m < M; ++m)
        {
            to_right[m] = max(current_costs[m], to_right[m - 1]) + map[n][m];
        }

        to_left[M - 1] = current_costs[M - 1] + map[n][M - 1];
        for (int m = M - 2; m >= 0; --m)
        {
            to_left[m] = max(current_costs[m], to_left[m + 1]) + map[n][m];
        }

        for (int m = 0; m < M; ++m)
            current_costs[m] = max(to_right[m], to_left[m]);
    }

    cout << current_costs[M - 1] << endl;

    return 0;
}