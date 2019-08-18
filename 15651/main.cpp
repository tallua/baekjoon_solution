#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


void permutation(int M, string str, int N, int last)
{
    if(M == 0)
    {
        cout << str << '\n';
        return;
    }

    if(str.size() != 0)
        str += ' ';
    for(int i = last; i < N; ++i)
    {
        permutation(M - 1, str + to_string(i + 1), N, i);
    }
}


int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    vector<bool> remain;
    remain.resize(N, true);

    permutation(M, "", N, 0);

    return 0;
}