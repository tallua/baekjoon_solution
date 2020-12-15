#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using count_t = int;
using mult_map = vector<pair<size_t, size_t>>;

const count_t mod_num = 9901;

constexpr size_t pow2(size_t N)
{
    return 1 << N;
}

void dfs(size_t from, size_t to, size_t N, size_t index, mult_map& multiply_map)
{
    if(index == N)
    {
        multiply_map.push_back({from, to});
        return;
    }

    size_t current_mask = 0x01 << index;
    size_t next_mask = 0x01 << (index + 1);
    
    size_t current = (from & current_mask) >> index;
    size_t next = (from & next_mask) >> (index + 1);

    if(current == 1)
    {
        dfs(from, to, N, index + 1, multiply_map);
    }
    else if(next == 1 || index + 1 == N)
    {
        dfs(from, to | current_mask, N, index + 1, multiply_map);
    }
    else
    {
        dfs(from, to, N, index + 2, multiply_map);
        dfs(from, to | current_mask, N, index + 1, multiply_map);
    }
}

mult_map gen_map(size_t N)
{
    mult_map multiply_map;

    for(size_t i = 0; i < pow2(N); ++i)
    {
        dfs(i, 0, N, 0, multiply_map);
    }

    return multiply_map;
}

void multiply(const vector<count_t>& prev, const mult_map& multiply_map, vector<count_t>& out)
{
    for(auto&& p : multiply_map)
    {
        out[p.second] += prev[p.first];
    }

    for(auto&& v : out)
    {
        v %= mod_num;
    }
}

int main(int argc, char** argv)
{
    size_t N, M;
    cin >> N >> M;

    auto multiply_map = gen_map(N);
    vector<count_t> result(pow2(N), 0);
    vector<count_t> buffer(pow2(N), 0);
    result[0] = 1;
    //cout << "map size: " << multiply_map.size() << endl;
    for(size_t m = 0; m < M; ++m)
    {
        multiply(result, multiply_map, buffer);
        swap(buffer, result);
        fill(buffer.begin(), buffer.end(), 0);
    }

    cout << result[0] << '\n';

    return 0;
}