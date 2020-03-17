#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <deque>
#include <algorithm>
#include <limits>

using namespace std;
using map_t = array<char, 2500>;
using count_map_t = array<int, 2500>;

const int int_max = numeric_limits<int>::max();

int fill(const map_t& map, const size_t& N, const vector<size_t>& virus_index, 
    count_map_t& count_map, const int& hint)
{

    for(size_t i = 0; i < N * N; ++i)
        count_map[i] = int_max;

    deque<size_t> current;
    for (const size_t& val : virus_index)
    {
        current.push_back(val);
        count_map[val] = 0;
    }

    while (!current.empty())
    {
        size_t indx = current.front();
        current.pop_front();
        
        if(indx % N != 0 && map[indx - 1] != '1' && count_map[indx - 1] == int_max)
        {
            count_map[indx - 1] = count_map[indx] + 1;
            current.push_back(indx - 1);
            if(map[indx - 1] == '0' && count_map[indx - 1] >= hint)
                return int_max;
        }
        
        if(indx % N != N - 1 && map[indx + 1] != '1' && count_map[indx + 1] == int_max)
        {
            count_map[indx + 1] = count_map[indx] + 1;
            current.push_back(indx + 1);
            if(map[indx + 1] == '0' && count_map[indx + 1] >= hint)
                return int_max;
        }
        
        if(indx / N != 0 && map[indx - N] != '1' && count_map[indx - N] == int_max)
        {
            count_map[indx - N] = count_map[indx] + 1;
            current.push_back(indx - N);
            if(map[indx - N] == '0' && count_map[indx - N] >= hint)
                return int_max;
        }
        
        if(indx / N != N - 1 && map[indx + N] != '1' && count_map[indx + N] == int_max)
        {
            count_map[indx + N] = count_map[indx] + 1;
            current.push_back(indx + N);
            if(map[indx + N] == '0' && count_map[indx + N] >= hint)
                return int_max;
        }
    }

    int max_seconds = 0;

    for(size_t indx = 0; indx < N * N; ++indx)
    {
        if(map[indx] == '0')
        {
            if(count_map[indx] == int_max)
                return int_max;
            max_seconds = max(max_seconds, count_map[indx]);
        }
    }

    return max_seconds;
}

void solve(const map_t &map, const size_t &N, const size_t &M, const vector<size_t> &virus_index, 
    vector<size_t> &enabled, size_t check_start, count_map_t& count_map, int& result)
{
    if (enabled.size() == M)
    {
        result = min(result, fill(map, N, enabled, count_map, result));
    }

    if(virus_index.size() - check_start < M - enabled.size())
        return;

    for (size_t i = check_start; i < virus_index.size(); ++i)
    {
        enabled.push_back(virus_index[i]);

        solve(map, N, M, virus_index, enabled, i + 1, count_map, result);

        enabled.pop_back();
    }
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N, M;
    cin >> N >> M;

    map_t map;
    vector<size_t> virus_index;
    for (size_t y = 0; y < N * N; ++y)
    {
        cin >> map[y];
        if (map[y] == '2')
            virus_index.push_back(y);
    }

    vector<size_t> enabled;
    enabled.reserve(M);

    count_map_t count_map;
    count_map.fill(int_max);

    int result = int_max;

    solve(map, N, M, virus_index, enabled, 0, count_map, result);

    if(result == int_max)
        cout << "-1\n";
    else
        cout << result << '\n';

    return 0;
}