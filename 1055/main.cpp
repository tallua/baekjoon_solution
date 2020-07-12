#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;
using len_t = long long;

const len_t LEN_MAX = 10000000000ll;

struct Input
{
    std::string str;
    std::string S;
    size_t replace_count;
    size_t non_replace_count;
};

vector<len_t> len_cache;

void init_len_cache(const Input& input, size_t R)
{
    len_cache.clear();
    len_cache.push_back(input.str.size());

    while(len_cache.size() <= R && len_cache.back() < LEN_MAX)
    {
        len_t last = len_cache.back();
        last = last * input.replace_count + input.non_replace_count;
        last = min(last, LEN_MAX);
        len_cache.push_back(last);
    }
}

len_t get_len_exp(size_t R)
{
    if(R < len_cache.size())
        return len_cache[R];
    return LEN_MAX;
}

void find_str_exp(const Input& input, size_t R, len_t begin, len_t end, ostringstream& oss)
{
    if(R == 0)
    {
        len_t head = 0;
        for(size_t i = 0; i < input.str.size(); ++i)
        {
            if(begin <= head && head < end)
            {
                oss << input.str[i];
            }
            head++;
        }
        return;
    }

    const len_t sub_len = get_len_exp(R - 1);
    len_t head = 0;
    for(size_t i = 0; i < input.S.size(); ++i)
    {
        if(input.S[i] == '$')
        {
            if(begin <= head + sub_len && head < end)
            {
                find_str_exp(input, R - 1, begin - head, end - head, oss);
            }
            head += sub_len;
        }
        else
        {
            if(begin <= head && head < end)
            {
                oss << input.S[i];
            }
            head++;
        }
    }
}

void find_str_1(const Input& input, size_t R, len_t begin, len_t end, ostringstream& oss)
{
    len_t total = input.str.size() + input.non_replace_count * len_t(R);
    while(begin < input.str.size() && begin < end && begin < total)
    {
        oss << input.str[begin];
        begin++;
    }

    const len_t str_size = input.str.size();
    const len_t div_size = input.non_replace_count;
    while(begin < end && begin < total)
    {
        oss << input.S[1 + ((begin - str_size) % div_size)];
        begin++;
    }
}

int main(int argc, char** argv)
{
    Input input;
    cin >> input.str;
    cin >> input.S;
    input.replace_count = 0;
    for(auto it = input.S.cbegin(); it != input.S.cend(); ++it)
    {
        if(*it == '$')
            input.replace_count++;
    }
    input.non_replace_count = input.S.size() - input.replace_count;

    size_t R;
    cin >> R;

    len_t begin, end;
    cin >> begin >> end;

    ostringstream oss;
    if(input.replace_count == 1)
    {
        find_str_1(input, R, begin - 1, end, oss);
    }
    else
    {
        init_len_cache(input, R);
        R = min(R, len_cache.size());
        find_str_exp(input, R, begin - 1, end, oss);
    }

    string result = oss.str();
    size_t result_len = end - begin + 1;

    cout << oss.str();
    for(size_t i = result.size(); i < result_len; ++i)
        cout << '-';
    cout << endl;
    
    return 0;
}
