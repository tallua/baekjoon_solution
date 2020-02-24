#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> a, b, c, d;
    a.resize(N);
    b.resize(N);
    c.resize(N);
    d.resize(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    map<int, size_t> ab, cd;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ab[a[i] + b[j]]++;
            cd[c[i] + d[j]]++;
        }
    }

    auto ab_it = ab.begin();
    auto cd_it = cd.rbegin();

    size_t answer = 0;

    while (ab_it != ab.end() && cd_it != cd.rend())
    {
        //cout << "checking : " << *ab_it << ", " << *cd_it << endl;
        auto sum = ab_it->first + cd_it->first;
        if (sum == 0)
        {
            answer += ab_it->second * cd_it->second;
            ab_it++;
            cd_it++;
        }
        else if (sum > 0)
        {
            cd_it++;
        }
        else
        {
            ab_it++;
        }
    }

    cout << answer << endl;

    return 0;
}