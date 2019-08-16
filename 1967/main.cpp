#include <iostream>
#include <array>
#include <vector>
#include <queue>

using namespace std;
using result_t = long long;

struct LinkInfo
{
    size_t node;
    int cost;
};

array<vector<LinkInfo>, 100001> links;

void dfs(size_t parent, size_t node, result_t& max, result_t& internal)
{
    max = 0;
    internal = 0;

    result_t max_1 = 0;
    result_t max_2 = 0;
    for(auto& link : links[node])
    {
        if(link.node == parent)
            continue;
        
        result_t tmp_m, tmp_internal;
        dfs(node, link.node, tmp_m, tmp_internal);
        result_t dist = tmp_m + link.cost;

        if(tmp_internal > internal)
            internal = tmp_internal;
        if(dist > max_1)
        {
            max_2 = max_1;
            max_1 = dist;
        }
        else if(dist > max_2)
        {
            max_2 = dist;
        }
    }

    max = max_1;
    if(internal < max_1 + max_2)
        internal = max_1 + max_2;
}   

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    size_t root = 1;
    int max_count = -1;
    int parent, child, cost;
    for(int n = 0; n < N - 1; ++n)
    {
        cin >> parent >> child >> cost;
        
        links[parent].push_back({child, cost});
        links[child].push_back({parent, cost});
    }
    
    // dummy root is 0
    links[0].push_back({root, 0});
    links[root].push_back({0, 0});

    result_t max, internal;
    dfs(0, root, max, internal);

    cout << internal << '\n';

    return 0;
}