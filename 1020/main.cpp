#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

using digit_seq = vector<int>;
using ll = long long;


constexpr int digit_to_line(const int digit)
{
    //                   0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    const int arr[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 5 };

    return arr[digit];
}

int count_lines(const digit_seq& arr)
{
    int sum = 0;
    for (const auto& val : arr)
        sum += digit_to_line(val);
    return sum;
}

int count_lines(const digit_seq& arr, size_t N)
{
    int sum = 0;
    for (size_t i = 0; i < N; ++i)
        sum += digit_to_line(arr[i]);
    return sum;
}

ll to_ll(const digit_seq& seq)
{
    ll result = 0;

    for (int indx = 0; indx < seq.size(); ++indx)
    {
        result *= 10;
        result += seq[indx];
    }

    return result;
}

constexpr ll pow10(int i)
{
    ll result = 1;
    while (i--) result *= 10;
    return result;
}

map<int, digit_seq> next_cache(const map<int, digit_seq>& before)
{
    map<int, digit_seq> next;

    for (int i = 0; i <= 9; ++i)
    {
        for (auto& b : before)
        {
            int cost = digit_to_line(i) + b.first;
            if (next.find(cost) == next.end())
            {
                digit_seq seq = { i };
                seq.insert(seq.end(), b.second.begin(), b.second.end());

                next.insert(make_pair(cost, seq));
            }
        }
    }

    return next;
}

digit_seq solve(const digit_seq& base, const int target)
{
    size_t indx = base.size() - 1;
    map<int, digit_seq> cache;
    cache.insert(make_pair(0, digit_seq()));

    do {
        digit_seq current = base;

        for (size_t i = indx + 1; i < current.size(); ++i)
        {
            current[i] = 0;
        }

        for (int i = current[indx] + 1; i <= 9; ++i)
        {
            current[indx] = i;

            const int remain = target - count_lines(current, indx + 1);
            const auto c_it = cache.find(remain);
            if (c_it != cache.end())
            {
                for (size_t i = 0; i < c_it->second.size(); ++i)
                {
                    current[indx + 1 + i] = c_it->second[i];
                }

                return current;
            }
        }

        // build next cache
        cache = next_cache(cache);

    } while (indx--);

    // check 00...00
    digit_seq zeros;
    zeros.resize(base.size(), 0);

    if (target == base.size() * digit_to_line(0))
    {
        return zeros;
    }

    // check after 00...00
    return solve(zeros, target);
}



int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string str;
    cin >> str;

    // str to vec
    vector<int> init_str;
    init_str.resize(str.size());
    for (size_t i = 0; i < str.size(); ++i)
    {
        init_str[i] = str[i] - '0';
    }

    const int target = count_lines(init_str);

    digit_seq result = solve(init_str, target);

    ll diff = to_ll(result) - to_ll(init_str);
    if (diff <= 0)
        diff = pow10(init_str.size()) + diff;

    cout << diff << endl;

    return 0;
}
