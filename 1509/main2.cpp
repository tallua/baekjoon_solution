#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    string str;
    cin >> str;

    const int N = str.length();

    vector<vector<bool>> pelin_cache;
    pelin_cache.resize(N);
    for (auto &row : pelin_cache)
        row.resize(N, false);

    // odd cache
    for (int i = 0; i < N; ++i)
    {
        for (int len = 0; len <= std::min(i, N - 1 - i); ++len)
        {
            if (str[i - len] == str[i + len])
            {
                pelin_cache[i - len][i + len] = true;
            }
            else
            {
                break;
            }
        }
    }

    // even cache
    for (int i = 0; i < N; ++i)
    {
        for (int len = 0; len <= std::min(i, N - i - 2); ++len)
        {
            if (str[i - len] == str[i + len + 1])
            {
                pelin_cache[i - len][i + len + 1] = true;
            }
            else
            {
                break;
            }
        }
    }

    // calc
    vector<int> min_count;
    min_count.resize(N);
    min_count[0] = 1;

    for (int i = 1; i < N; ++i)
    {
        int tmp_min = min_count[i - 1] + 1;
        if (pelin_cache[0][i])
        {
            tmp_min = 1;
        }
        else
        {
            for (int j = 1; j < i; ++j)
            {
                if (pelin_cache[j][i] && min_count[j - 1] + 1 < tmp_min)
                {
                    tmp_min = min_count[j - 1] + 1;
                }
            }
        }

        min_count[i] = tmp_min;
    }
    
    cout << min_count[N - 1] << endl;

    return 0;
}
