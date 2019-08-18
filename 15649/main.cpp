#include <iostream>
#include <string>
#include <vector>

using namespace std;


void permutation(int M, string str, vector<bool>& remain)
{
    if(M == 0)
    {
        cout << str << '\n';
        return;
    }

    if(str.size() != 0)
        str += ' ';
    for(int i = 0; i < remain.size(); ++i)
    {
        bool remained = remain[i];
        if(remained == false)
            continue;

        remain[i] = false;
        permutation(M - 1, str + to_string(i + 1), remain);
        remain[i] = true;
    }
}


int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    vector<bool> remain;
    remain.resize(N, true);

    permutation(M, "", remain);

    return 0;
}