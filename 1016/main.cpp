#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using num_t = long long;

size_t solve(num_t min_num, num_t max_num)
{
    num_t max_sqrt = (num_t)(sqrtl(max_num));

    vector<bool> is_sqrnono;
    is_sqrnono.resize(max_num - min_num + 1, true);

    vector<bool> is_prime;
    is_prime.resize(max_sqrt + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;

    
    size_t count = max_num - min_num + 1;
    for(size_t i = 2; i < max_sqrt + 1; ++i)
    {
        if(is_prime[i] == false)
            continue;

        for(size_t j = 2 * i; j < max_sqrt + 1; j += i)
            is_prime[j] = false;

        num_t sqr = i * i;
        num_t min_sqr = (min_num / sqr) * sqr;
        if(min_sqr < min_num)
            min_sqr += sqr;
        for(num_t j = min_sqr; j <= max_num; j += sqr)
        {
            if(is_sqrnono[j - min_num])
                count--;
            is_sqrnono[j - min_num] = false;
        }
    }

    return count;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    num_t min_num, max_num;
    cin >> min_num >> max_num;

    //num_t prev = 0;
    //for(num_t i = min_num; i < max_num; ++i)
    //{
    //    num_t cur = solve(min_num, i);
    //
    //    if(cur == prev)
    //        cout << i << " : " << cur << endl;
    //    prev = cur;
    //}

    cout << solve(min_num, max_num) << endl;

    return 0;
}
