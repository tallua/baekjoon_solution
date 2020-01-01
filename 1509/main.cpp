#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

bool is_pelindrom(const char* const view, size_t begin, size_t end)
{
    if(begin >= end)
        return false;

    end--;
    while(begin != end)
    {
        if(view[begin] != view[end])
            return false;

        begin++;
        if(begin == end)
            break;
        end--;
    }

    return true;
}

int count_pelindrom(const char* const str, const size_t begin, const size_t end, vector<int>& cache)
{
    if(begin >= end)
        return 0;
    
    if(cache[begin] != -1)
        return cache[begin];

    int min_count = numeric_limits<int>::max();

    for(int mid = begin + 1; mid <= end; ++mid)
    {
        if(is_pelindrom(str, begin, mid))
        {
            min_count = min(min_count, count_pelindrom(str, mid, end, cache) + 1);
        }
    }

    cache[begin] = min_count;

    return min_count;
}

int main(int arg, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string str;
    cin >> str;

    vector<int> cache;
    cache.resize(str.size(), -1);

    cout << count_pelindrom(str.data(), 0, str.size(), cache) << endl;

    return 0;
}