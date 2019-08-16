#include <iostream>
#include <array>

using namespace std;

enum { R = 0, G = 1, B = 2 };

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    array<size_t, 3> costs;
    costs.fill(0);

    for(int i = 0; i < N; ++i)
    {
        int cost_r, cost_g, cost_b;
        cin >> cost_r >> cost_g >> cost_b;

        array<size_t, 3> next_costs;
        next_costs[R] = min(costs[G], costs[B]) + cost_r;
        next_costs[G] = min(costs[R], costs[B]) + cost_g;
        next_costs[B] = min(costs[R], costs[G]) + cost_b; 

        costs = next_costs;
    }
    
    cout << min(costs[R], min(costs[G], costs[B])) << '\n';

    return 0;
}


