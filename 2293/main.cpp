#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    vector<int> coins;
    coins.reserve(N);

    for(int n = 0; n < N; ++n)
    {
        int tmp;
        cin >> tmp;
        if(tmp <= K)
            coins.push_back(tmp);
    }

    sort(coins.begin(), coins.end());

    if(coins.size() == 0)
    {
        cout << "0\n";
        return 0;
    }

    vector<int> cache;
    cache.resize(K + 1, 0);
    {
        int coin = coins[0];
        int max_cnt = K / coin;
        for(int i = 0; i <= max_cnt; ++i)
        {
            cache[i * coin] = 1;
        }
    }
    

    for(int c_it = 1; c_it < coins.size(); ++c_it)
    {
        vector<int> cache_tmp;
        cache_tmp.resize(K + 1, 0);

        int coin = coins[c_it];
        int max_cnt = K / coin;
        for(int i = 0; i <= K; ++i)
        {
            int tmp = 0;
            
            if(i - coin >= 0)
            {
                cache_tmp[i] = cache[i] + cache_tmp[i - coin];
            }
            else
            {
                cache_tmp[i] = cache[i];
            }
        }

        cache = cache_tmp;
    }
    
    cout << cache[K] << '\n';
    

    return 0;
}