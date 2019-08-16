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

    int V;
    cin >> V;

    size_t root = 0;
    int max_count = -1;
    int node, count, other, cost;
    for(int v = 0; v < V; ++v)
    {
        cin >> node;
        
        count = 0;
        do{
            cin >> other;
            if(other != -1)
            {
                cin >> cost;

                links[node].push_back(LinkInfo{other, cost});
                count+= 1;
            }
        } while(other != -1);

        if(count > max_count)
        {
            root = node;
            max_count = count;
        }
    }
    
    // dummy root is 0
    links[0].push_back({root, 0});
    links[root].push_back({0, 0});

    result_t max, internal;
    dfs(0, root, max, internal);

    cout << internal << '\n';

    return 0;
}