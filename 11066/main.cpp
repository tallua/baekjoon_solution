#include <iostream>
#include <vector>

using namespace std;


using filesize_t = int;
struct file
{
    filesize_t size;
    filesize_t cost;
};
using cost_t = vector<vector<file>>;


filesize_t calc(const vector<filesize_t>& files)
{
    const size_t N = files.size();
    cost_t cost;
    cost.resize(N);
    for(size_t i = 0; i < N; ++i)
    {
        cost[i].resize(N, {0, 0});
        cost[i][i] = { files[i], 0 };
    }

    for(size_t dist = 1; dist < N; ++dist)
    {
        for(size_t start = 0; start < N - dist; ++start)
        {
            size_t end = start + dist;
            
            if(dist == 1)
            {
                filesize_t fs = cost[start][start].size + cost[end][end].size;
                filesize_t fc = fs;
                cost[start][end] = { fs, fs };
                cost[end][start] = { fs, fs };
            }
            else
            {
                filesize_t fs = cost[start][start].size + cost[start + 1][end].size;
                
                filesize_t min = 10000000000;
                for(size_t mid = start; mid < end; ++mid)
                {
                    filesize_t fc = cost[start][mid].cost + cost[mid + 1][end].cost;
                    if(fc < min)
                        min = fc;
                }
                
                cost[start][end] = { fs, min + fs };
                cost[end][start] = { fs, min + fs };
            }
        }
    }

    return cost[0][N - 1].cost;
}

int main(int argc, char** argv)
{
    int T;
    cin >> T;

    for(int t = 0; t < T; ++t)
    {
        int N;
        cin >> N;
        
        vector<filesize_t> list;
        list.resize(N);
        for(int n = 0; n < N; ++n)
        {
            cin >> list[n];
        }

        cout << calc(list) << '\n';

    }

    return 0;
}






