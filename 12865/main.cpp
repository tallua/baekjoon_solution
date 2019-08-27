#include <iostream>
#include <array>
#include <vector>
#include <algorithm>


using namespace std;



int main(int argc, char** argv)
{
    int N, K;
    cin >> N >> K;

    vector<array<int, 2>> objects;
    objects.resize(N);
    for(int n = 0; n < N; ++n)
    {
        cin >> objects[n][0] >> objects[n][1];
    }

    sort(objects.begin(), objects.end(), [](auto& lhs, auto& rhs) { return lhs[0] < rhs[0]; });

    using val_list_t = array<int, 100001>;
    val_list_t cache;
    cache.fill(0);

    for(int n = 0; n < N; ++n)
    {
        int w_next = objects[n][0];
        int v_next = objects[n][1];

        val_list_t cache_next;
        for(int k = 0; k <= K; ++k)
        {
            if(k - w_next >= 0)
            {
                cache_next[k] = max(cache[k], cache[k - w_next] + v_next);
            }
            else
            {
                cache_next[k] = cache[k];
            }
        }

        cache = cache_next;
    }

    cout << cache[K] << '\n';

    return 0;
}


