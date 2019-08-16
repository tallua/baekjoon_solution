
#include <cstdio>
#include <vector>
#include <stack>
#include <array>
#include <set>

using namespace std;

array<vector<size_t>, 100001> links;
array<size_t, 100001> parent;

int main(int argc, char** argv)
{

    int N;
    scanf("%d", &N);

    for(int n = 0; n < N - 1; ++n)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        links[x].push_back(y);
        links[y].push_back(x);
    }


    stack<size_t> checking;
    checking.push(1);
    parent[1] = 1;

    while(checking.size() != 0)
    {
        size_t now = checking.top();
        checking.pop();

        for(auto& link : links[now])
        {
            if(parent[link] == 0)
            {
                parent[link] = now;
                checking.push(link);
                
            }
        }

        links[now].clear();
    }

    for(size_t n = 2; n < N + 1; ++n)
    {
        printf("%d\n", parent[n]);
    }


    return 0;
}