#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using val_t = long long;

val_t find_min(const vector<vector<val_t>>& segtree, int depth, int a, int b);

val_t find_min(const vector<vector<val_t>>& segtree, int depth, int a, int b)
{
    val_t tmp = segtree[depth][b];
    if(a == b)
        return segtree[depth][b];

    if(a % 2 == 1)
    {
        tmp = std::min(tmp, segtre e[depth][a]);
        a++;
    }
    if(b % 2 == 0)
    {
        tmp = std::min(tmp, segtree[depth][b]);
        b--;
    }

    if(a < b)
        tmp = std::min(tmp, find_min(segtree, depth + 1, a / 2, b / 2));
    
    return tmp;}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    
    vector<vector<val_t>> segtree;
    segtree.resize(1);
    segtree[0].resize(N);
    for(int n = 0; n < N; ++n)
    {
        cin >> segtree[0][n];
    }

    // build seg-tree
    while(segtree.back().size() > 1)
    {
        const auto& last = segtree.back();
        vector<val_t> arr;
        arr.resize(last.size() / 2);

        for(int i = 0; i < arr.size(); ++i)
        {
            arr[i] = std::min(last[i * 2], last[i * 2 + 1]);
        }
        
        segtree.push_back(arr);
    }

    for(int m = 0; m < M; ++m)
    {
        int a, b;
        cin >> a >> b;
        a = min(a, N);
        b = min(b, N);
        a--;
        b--;

        if(a > b)
        {
            auto tmp = a;
            a = b;
            b = tmp;
        }

        cout << find_min(segtree, 0, a, b) << '\n';
    }

    return 0;
}
