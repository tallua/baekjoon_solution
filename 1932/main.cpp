#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    size_t N;
    cin >> N;

    array<array<size_t, 501>, 501> costs;

    for(int i = 1; i <= N; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            size_t C;
            cin >> C;

            size_t tmp = 0;
            if(j == 0)
            {
                costs[i][j] = C + costs[i - 1][j];
            }
            else
            {
                costs[i][j] = C + max(costs[i - 1][j - 1], costs[i - 1][j]);
            }
        }
    }

    size_t max = *max_element(costs[N].data(), costs[N].data() + N);

    cout << max << '\n';

    return 0;
}


