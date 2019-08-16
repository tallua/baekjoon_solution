#include <iostream>
#include <vector>
#include <stack>


using namespace std;
using map_t = vector<vector<int>>;


#define MAX_VAL 10000

int trace(const map_t& map, int n, int m, const int& N, const int& M, map_t& cache)
{
    if(n == N - 1 && m == M - 1)
        return 1;
    if(cache[n][m] != -1)
        return cache[n][m];

    int now = map[n][m];
    int left = m >= 1 ? map[n][m - 1] : MAX_VAL;
    int right = m <= M - 2 ? map[n][m + 1] : MAX_VAL;
    int up = n >= 1 ? map[n - 1][m] : MAX_VAL;
    int down = n <= N - 2 ? map[n + 1][m] : MAX_VAL;

    int cnt = 0;
    if(now > left)
        cnt += trace(map, n, m - 1, N, M, cache);
    if(now > right)
        cnt += trace(map, n, m + 1, N, M, cache);
    if(now > up)
        cnt += trace(map, n - 1, m, N, M, cache);
    if(now > down)
        cnt += trace(map, n + 1, m, N, M, cache);

    cache[n][m] = cnt;
    return cnt;
}


int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    map_t map;
    map_t cache;
    map.resize(N);
    cache.resize(N);
    for(int n = 0; n < N; ++n)
    {
        map[n].resize(M);
        cache[n].resize(M);
        for(int m = 0; m < M; ++m)
        {
            cin >> map[n][m];
            cache[n][m] = -1;
        }
    }

    cout << trace(map, 0, 0, N, M, cache) << endl;

    return 0;
}
