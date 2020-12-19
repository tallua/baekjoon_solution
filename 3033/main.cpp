#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

std::vector<size_t> build_suffix_array(const std::string &str)
{
    using namespace std;

    const size_t str_len = str.size();
    const size_t N = str_len + 1;

    // initialize

    auto front_sort = [](vector<size_t> &order, const vector<size_t> &group, const vector<size_t> &back_sorted, size_t N) {
        size_t counter_len = 0;
        vector<size_t> counter(N < 256 ? 256 : N, 0);
        for (size_t n = 0; n < N; ++n)
        {
            counter[group[n]]++;
            counter_len = counter_len < group[n] ? group[n] : counter_len;
        }
        counter_len++;

        for (size_t c_index = 1; c_index < counter_len; ++c_index)
        {
            counter[c_index] += counter[c_index - 1];
        }

        // reverse iterate for stable sort
        size_t n = N;
        do
        {
            n--;
            order[--counter[group[back_sorted[n]]]] = back_sorted[n];
        } while (n != 0);
    };

    auto regroup = [](vector<size_t> &group, const vector<size_t> &order, size_t shift, size_t N) {
        size_t group_cnt = 0;
        vector<size_t> group_next(N);
        group_next[order[0]] = group_cnt++;
        for (size_t n = 1; n < N; ++n)
        {
            if (group[order[n]] != group[order[n - 1]] ||
                group[(order[n] + shift) % N] != group[(order[n - 1] + shift) % N])
            {
                group_cnt++;
            }

            group_next[order[n]] = group_cnt - 1;
        }

        group.swap(group_next);
    };

    vector<size_t> orders(N, 0);
    vector<size_t> group(N);
    vector<size_t> orders_shifted(N);

    for (size_t n = 0; n < str_len; ++n)
    {
        group[n] = str[n];
        orders_shifted[n] = n;
    }
    group[str_len] = '$';
    orders_shifted[str_len] = str_len;

    // step 0
    front_sort(orders, group, orders_shifted, N);
    regroup(group, orders, 0, N);

    // sort from step 1
    for (size_t range = 1; range < N; range = range << 1)
    {
        for (size_t n = 0; n < N; ++n)
        {
            if (orders[n] < range)
                orders_shifted[n] = N + orders[n] - range;
            else
                orders_shifted[n] = orders[n] - range;
        }

        front_sort(orders, group, orders_shifted, N);
        regroup(group, orders, range, N);
    }

    std::vector<size_t> result(str_len);
    auto result_it = result.begin();
    for(auto order_it = ++orders.begin(); order_it < orders.end(); ++order_it, ++result_it)
    {
        *result_it = *order_it;
    }
    return result;
}



int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int dummy;
    cin >> dummy;

    std::string str;
    cin >> str;

    vector<size_t> sa = build_suffix_array(str);

    vector<size_t> index_to_suffix;
    index_to_suffix.resize(str.size());
    for(size_t i = 0; i < str.size(); ++i)
    {
        index_to_suffix[sa[i]] = i;
    }

    //vector<size_t> lcp;
    //lcp.resize(str.size(), -1);

    size_t match_index = 0;
    size_t max_match = 0;
    for(size_t i = 0; i < str.size(); ++i)
    {
        size_t suffix_index = index_to_suffix[i];
        if(suffix_index == str.size() - 1)
        {
            match_index = 0;
            continue;
        }

        size_t current_pos = sa[suffix_index];
        size_t other_pos = sa[suffix_index + 1];
        while(str[current_pos + match_index] == str[other_pos + match_index])
            match_index++;

        //lcp[suffix_index] = match_index;
        max_match = max(max_match, match_index);

        if(match_index)
            match_index--;
    }
    cout << max_match << '\n';

    return 0;
}


