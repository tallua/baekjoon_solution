#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct LCS
{
    string str1;
    string str2;

    LCS(const string& str1, const string& str2)
        : str1(str1), str2(str2)
    {
    }

    int solve()
    {
        vector<int> cache;
        cache.resize(str1.size() + 1, 0);
        
        for(int i2 = 0; i2 < str2.size(); ++i2)
        {
            vector<int> tmp;
            tmp.resize(str1.size() + 1, 0);
            for(int i1 = 0; i1 < str1.size(); ++i1)
            {
                if(str2[i2] == str1[i1])
                {
                    tmp[i1 + 1] = max(cache[i1] + 1, max(cache[i1 + 1], tmp[i1]));
                }
                else
                {
                    tmp[i1 + 1] = max(cache[i1 + 1], tmp[i1]);
                }
                
            }

            cache = tmp;
        }

        return cache[str1.size()];
    }
    
};


int main(int argc, char** argv)
{
    string str1;
    string str2;

    cin >> str1;
    cin >> str2;
    
    LCS lcs(str1, str2);
    cout << lcs.solve() << '\n';

    return 0;
}