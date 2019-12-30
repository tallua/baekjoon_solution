#include <iostream>
#include <vector>

using namespace std;


void print(const vector<vector<int>>& predecessor, vector<bool>& printed, int nth)
{
    if(printed[nth] == true)
        return;

    for(auto& pre : predecessor[nth])
    {
        print(predecessor, printed, pre);
    }

    printed[nth] = true;
    cout << (nth + 1) << ' ';
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> predecessor;
    predecessor.resize(N);

    for(int m = 0; m < M; ++m)
    {
        int A, B;
        cin >> A >> B;

        predecessor[B - 1].push_back(A - 1);
    }

    vector<bool> printed;
    printed.resize(N, false);
    
    for(int n = 0; n < N; ++n)
    {
        print(predecessor, printed, n);
    }

    cout << endl;

    return 0;
}