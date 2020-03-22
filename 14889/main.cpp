#include <iostream>
#include <vector>
#include <array>
#include <limits>

using namespace std;
using ability_t = int;

ability_t calc_diff(const size_t half_N, const array<array<ability_t, 20>, 20>& synergy, const vector<size_t>& team_a, const vector<size_t>& team_b)
{
    ability_t abil_a = 0, abil_b = 0;

    for(size_t i = 0; i < half_N; ++i)
    {
        for(size_t j = i + 1; j < half_N; ++j)
        {
            abil_a += synergy[team_a[i]][team_a[j]];
        }
    }
    
    for(size_t i = 0; i < half_N; ++i)
    {
        for(size_t j = i + 1; j < half_N; ++j)
        {
            abil_b += synergy[team_b[i]][team_b[j]];
        }
    }

    if(abil_a > abil_b)
        return abil_a - abil_b;
    return abil_b - abil_a;
}

ability_t dfs(const size_t N, const array<array<ability_t, 20>, 20>& synergy, vector<size_t>& team_a, vector<size_t>& team_b, size_t index)
{
    const size_t half_N = N / 2;
    if(index == N)
        return calc_diff(half_N, synergy, team_a, team_b);


    ability_t result = numeric_limits<ability_t>::max();

    if(team_a.size() < half_N)
    {
        team_a.push_back(index);
        result = min(result, dfs(N, synergy, team_a, team_b, index + 1));
        team_a.pop_back();
    }

    if(team_b.size() < half_N)
    {
        team_b.push_back(index);
        result = min(result, dfs(N, synergy, team_a, team_b, index + 1));
        team_b.pop_back();
    }

    return result;
}


ability_t dfs(const size_t N, const array<array<ability_t, 20>, 20>& synergy)
{
    vector<size_t> team_a, team_b;
    team_a.reserve(N / 2);
    team_b.reserve(N / 2);

    return dfs(N, synergy, team_a, team_b, 0);
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;
    
    array<array<ability_t, 20>, 20> synergy;
    for(size_t y = 0; y < N; ++y)
    {
        for(size_t x = 0; x < N; ++x)
        {
            cin >> synergy[y][x];
        }
    }

    for(size_t y = 0; y < N; ++y)
    {
        for(size_t x = y + 1; x < N; ++x)
        {
            synergy[y][x] += synergy[x][y];
            synergy[x][y] = synergy[y][x];
        }
    }

    cout << dfs(N, synergy) << endl;

    return 0;
}