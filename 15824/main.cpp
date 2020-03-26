#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using scoville_t = long long;

#define MOD_NUM 1000000007LL

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;
    
    vector<scoville_t> scovilles;
    scovilles.resize(N);

    for(size_t n = 0; n < N; ++n)
    {
        cin >> scovilles[n];
    }

    sort(scovilles.begin(), scovilles.end());

    scoville_t pow_n = 2;
    scoville_t sum = 0;
    scoville_t last = 0;
    for(size_t n = 1; n < N; ++n)
    {
        scoville_t diff = scovilles[n] - scovilles[n - 1];
        last = ((last * 2) + diff * (pow_n - 1)) % MOD_NUM;
        sum = (sum + last) % MOD_NUM;
        pow_n = (pow_n * 2) % MOD_NUM;
    }

    cout << sum << endl;

    return 0;
}