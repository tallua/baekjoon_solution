#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using cost_t = long long;

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N, T;
    cin >> N >> T;

    vector<cost_t> costs(N);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> costs[n];
    }

    vector<cost_t> initial_costs(N);
    vector<cost_t> max_delta_costs(N);

    initial_costs[0] = 0;
    max_delta_costs[0] = 0;

    for(size_t n = 1; n < N; ++n)
    {
        initial_costs[n] += initial_costs[n - 1] + costs[n] + costs[n - 1];
        max_delta_costs[n] = max(max_delta_costs[n - 1], costs[n] + costs[n - 1]);
    }

    size_t half_T = T / 2;
    cost_t total_max_cost = 0;
    for(size_t n = 0; n < N && n <= half_T; ++n)
    {
        cost_t current_cost = initial_costs[n] + max_delta_costs[n] * (half_T - n);
        //cout << n << " : " << initial_costs[n] << " + " << max_delta_costs[n] << " * " << (half_T - n) << " = " << current_cost << endl;
        total_max_cost = max(total_max_cost, current_cost);
    }

    cout << total_max_cost << '\n';

    return 0;
}