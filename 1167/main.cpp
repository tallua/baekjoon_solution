#include <iostream>
#include <array>
#include <vector>
#include <queue>

using namespace std;
using result_t = long long;

struct LinkInfo
{
    int node;
    int cost;
};

array<vector<LinkInfo>, 100001> links;

pair<result_t, result_t> max2_dist(size_t prev, size_t from);

result_t max_dist(size_t node)
{
    if(links[node].size() == 1 && links[links[node][0].node].size() == 1)
        return links[node][0].cost;

    auto dist = max2_dist(0, node);
    return dist.second;
}

pair<result_t, result_t> max2_dist(size_t prev, size_t from)
{
    if(links[from].size() == 1)
        return make_pair(0, 0);
        
    result_t max_internal = 0;
    priority_queue<result_t> max_out;
    for(auto& others : links[from])
    {
        if(others.node == prev)
            continue;

        auto dist = max2_dist(from, others.node);
        
        if(max_internal < dist.second)
            max_internal = dist.second;
        
        max_out.push(dist.first + others.cost);
    }

    result_t max = max_out.top();
    max_out.pop();

    if(max_out.size() != 0)
    {
        result_t internal = max_out.top() + max;
        if(internal > max_internal)
            max_internal = internal;
    }

    return make_pair(max, max_internal);    
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int V;
    cin >> V;

    int max_node = -1;
    int max_count = -1;
    for(int v = 0; v < V; ++v)
    {
        int node;
        cin >> node;

        int count = 0;
        int other = -1;
        do{
            cin >> other;
            if(other != -1)
            {
                int cost;
                cin >> cost;

                links[node].push_back(LinkInfo{other, cost});
                count+= 1;
            }
        } while(other != -1);

        if(count > max_count)
        {
            max_node = node;
            max_count = count;
        }
    }
    
    auto dist = max_dist(max_node);

    cout << dist << '\n';

    return 0;
}
