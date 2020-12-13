#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;
using height_t = int;

const size_t max_n = 50;
const height_t max_height = 500000;

array<array<height_t, max_height + 1>, max_n + 1> cache;

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    height_t total_sum = 0;
    vector<height_t> block_heights(N);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> block_heights[n];
        total_sum += block_heights[n];
    }

    sort(block_heights.begin(), block_heights.end());

    cache[0][0] = 0;
    cache[0][block_heights[0]] = block_heights[0];
    for(size_t i = 1; i < N; ++i)
    {
        height_t current = block_heights[i];
        cache[i][current] = max(cache[i][current], cache[i - 1][0] + current);
        for(height_t j = 0; j <= total_sum; ++j)
        {
            if(cache[i - 1][j] == 0)
                continue;
            
            height_t prev = cache[i - 1][j];
            cache[i][j] = max(cache[i][j], prev);
            cache[i][j + current] = max(cache[i][j + current], prev + current);
            if(j - current < 0)
            {
                cache[i][current  - j] = max(cache[i][current  - j], prev - j + current);
            }
            else
            {
                cache[i][j - current] = max(cache[i][j - current], prev);
            }
        }
    }

    //for(size_t i = 0; i < N; ++i)
    //{
    //    for(height_t h = 0; h < 15; ++h)
    //    {
    //        printf("%3d", cache[i][h]);
    //    }
    //    cout << endl;
    //}

    height_t result = cache[N - 1][0];

    cout << (result != 0 ? result : -1) << '\n';

    return 0;
}