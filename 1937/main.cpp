#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

using map_t = vector<vector<int>>;
const int map_undef = -1;

void dfs(const int N, const map_t &map, map_t &cache, int px, int py)
{
    if (cache[py][px] != map_undef)
        return;

    int max_val = 1;
    if (px > 0 && map[py][px] > map[py][px - 1])
    {
        dfs(N, map, cache, px - 1, py);
        max_val = max(max_val, cache[py][px - 1] + 1);
    }
    if (py > 0 && map[py][px] > map[py - 1][px])
    {
        dfs(N, map, cache, px, py - 1);
        max_val = max(max_val, cache[py - 1][px] + 1);
    }
    if (px < N - 1 && map[py][px] > map[py][px + 1])
    {
        dfs(N, map, cache, px + 1, py);
        max_val = max(max_val, cache[py][px + 1] + 1);
    }
    if (py < N - 1 && map[py][px] > map[py + 1][px])
    {
        dfs(N, map, cache, px, py + 1);
        max_val = max(max_val, cache[py + 1][px] + 1);
    }

    cache[py][px] = max_val;
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    map_t map;
    map.resize(N);
    for (auto &row : map)
        row.resize(N);

    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            cin >> map[y][x];
        }
    }

    map_t cache;
    cache.resize(N);
    for (auto &row : cache)
        row.resize(N, map_undef);

    int max_val = 0;
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            dfs(N, map, cache, x, y);
            max_val = max(max_val, cache[y][x]);
        }
    }

    cout << max_val << endl;

    return 0;
}