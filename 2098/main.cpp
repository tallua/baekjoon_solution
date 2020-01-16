#include <iostream>

#include <vector>
#include <map>
#include <unordered_set>

using namespace std;
using cost_t = vector<vector<int>>;
using visited_t = unordered_set<int>;
using cache_t = vector<map<int, int>>;

int hash_visited(const unordered_set<int>& visited)
{
    int result = 0;

    for(auto i : visited)
    {
        result = result | (1 << i);
    }

    return result;
}

int dfs(const cost_t& costmap, visited_t& visited, int last, cache_t& cache)
{
    const int N = costmap.size();

    if(visited.size() == N)
    {
        return costmap[last][0];
    }
    
    int hashed = hash_visited(visited);
    auto cached = cache[last].find(hashed);
    if(cached != cache[last].end())
        return cached->second;

    const int unavailable_cost = 0;
    int min_val = unavailable_cost;
    for(int i = 0; i < N; ++i)
    {
        if(visited.find(i) == visited.end() && costmap[last][i] != 0)
        {
            visited.insert(i);
            int cost = dfs(costmap, visited, i, cache);
            visited.erase(i);

            if(cost == unavailable_cost)
            {
                continue;
            }

            cost += costmap[last][i];

            if(min_val == unavailable_cost || cost < min_val)
                min_val = cost;
        }
    }

    //cout << last << " : ";
    //for(auto v : visited)
    //{
    //    cout << v << ' ';
    //}
    //cout << " : " << hashed;
    //cout << " : " << min_val << endl;

    cache[last][hashed] = min_val;

    return min_val;
}


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    cost_t costmap;
    costmap.resize(N);
    for(int ny = 0; ny < N; ++ny)
    {
        costmap[ny].resize(N);
        for(int nx = 0; nx < N; ++nx)
        {
            cin >> costmap[ny][nx];
        }
    }

    visited_t visited;
    visited.insert(0);

    cache_t cache;
    cache.resize(N);

    cout << dfs(costmap, visited, 0, cache) << endl;

    return 0;
}


