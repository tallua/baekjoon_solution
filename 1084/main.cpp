#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;
using len_t = unsigned long long;
using cost_t = unsigned long long;

#define MAX_COST 1000000000000000001ULL




void testCase(const size_t N)
{
    array<cost_t, 10> costs;
    costs.fill(MAX_COST + 1);
    for (size_t n = 0; n < N; ++n)
        cin >> costs[n];

    cost_t C;
    cin >> C;

    array<size_t, 10> cost_order;
    for (size_t n = 0; n < cost_order.size(); ++n)
        cost_order[n] = n;

    sort(cost_order.begin(), cost_order.end(), [&](const size_t& lhs, const size_t& rhs) {
        return costs[lhs] < costs[rhs];
    });

    len_t total_length = 0;
    vector<size_t> num_front;
    num_front.reserve(50);
    vector<size_t> num_back;
    num_back.reserve(50);


    const bool num_exist = costs[cost_order[0]] <= C;
    const bool is_zero = N == 1 || (cost_order[0] == 0 && C < costs[cost_order[1]]);

    if (num_exist)
    {
        if (is_zero)
        {
            total_length = 1;
            num_front.push_back(0);
            num_back.push_back(0);
        }
        else
        {
            size_t first_index = 0;
            if (cost_order[0] == 0)
                first_index = 1;

            const size_t first_num = cost_order[first_index];
            total_length += 1;
            C -= costs[first_num];
            total_length += (C / costs[cost_order[0]]);
            C %= costs[cost_order[0]];

            if (total_length <= 50)
            {
                num_front.push_back(first_num);
                num_front.resize(total_length, cost_order[0]);
                num_back.push_back(first_num);
                num_back.resize(total_length, cost_order[0]);
            }
            else
            {
                num_front.push_back(first_num);
                num_front.resize(50, cost_order[0]);
                num_back.resize(50, cost_order[0]);
            }

            for (size_t n = N - 1; n > 0; --n)
            {
                if (costs[cost_order[n]] - costs[first_num] <= C)
                {
                    C -= costs[cost_order[n]] - costs[first_num];
                    num_front[0] = cost_order[n];
                    if (total_length <= 50)
                        num_back[0] = cost_order[n];
                    break;
                }
            }

            const len_t front_start = 0;
            const len_t front_end = (len_t)num_front.size();
            const len_t back_start = total_length - (len_t)num_back.size();
            const len_t back_end = total_length;

            len_t current_index = 1;
            for (size_t n = N - 1; n > 0; --n)
            {
                if (costs[cost_order[n]] - costs[cost_order[0]] <= C)
                {
                    cost_t upgrade_cost = costs[cost_order[n]] - costs[cost_order[0]];
                    len_t upgrade_len = upgrade_cost == 0? total_length - current_index : (C / upgrade_cost);
                    if(upgrade_len > total_length - current_index)
                        upgrade_len = total_length - current_index;

                    const len_t upgrade_start = current_index;
                    const len_t upgrade_end = current_index + upgrade_len;

                    if (upgrade_start < front_end)
                    {
                        size_t start_index = upgrade_start;
                        size_t end_index = front_end < upgrade_end ? front_end : upgrade_end;
                        for (size_t i = start_index; i < end_index; ++i)
                        {
                            num_front[i] = cost_order[n];
                        }
                    }

                    if (upgrade_end >= back_start)
                    {
                        size_t start_index = upgrade_start < back_start ? 0 : upgrade_start - back_start;
                        size_t end_index = upgrade_end - back_start;
                        for (size_t i = start_index; i < end_index; ++i)
                        {
                            num_back[i] = cost_order[n];
                        }
                    }

                    C -= upgrade_len * upgrade_cost;
                    current_index += upgrade_len;

                    if (current_index >= total_length)
                        break;
                }
            }
        }

    }

    // print
    cout << total_length << '\n';
    for (size_t n = 0; n < num_front.size(); ++n)
        cout << num_front[n];
    cout << '\n';
    for (size_t n = 0; n < num_back.size(); ++n)
        cout << num_back[n];
    cout << '\n';
}


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    while (cin >> N)
    {
        testCase(N);
    }

    cout << endl;

    return 0;
}