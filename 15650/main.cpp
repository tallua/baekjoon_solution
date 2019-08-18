#include <iostream>
#include <string>
#include <algorithm>
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
    auto last_false = find_if(remain.rbegin(), remain.rend(), [](bool val) { return val == false; });
    int start = distance(last_false, remain.rend());
    
    for(int i = start; i < remain.size(); ++i)
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