#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    // dimension info
    array<int, 2> dim_size;
    for (int dim_indx = 0; dim_indx < dim_size.size(); ++dim_indx)
    {
        cin >> dim_size[dim_indx];
    }
    // tomato info
    vector<int> tomato_state;
    vector<int> current;
    tomato_state.resize(dim_size[0] * dim_size[1]);
    for (int tomato_indx = 0; tomato_indx < tomato_state.size(); ++tomato_indx)
    {
        cin >> tomato_state[tomato_indx];
        if (tomato_state[tomato_indx] == 1)
            current.push_back(tomato_indx);
    }

    // simulate info
    int day = 0;
    vector<int> next;
    while (!current.empty())
    {
        while (!current.empty())
        {
            auto cur_indx = current.back();
            current.pop_back();

            int tomato_x = cur_indx % dim_size[0];
            int tomato_y = cur_indx / dim_size[0];

            if (tomato_x != 0)
            {
                const auto next_indx = cur_indx - 1;
                if (tomato_state[next_indx] == 0)
                {
                    tomato_state[next_indx] = 1;
                    next.push_back(next_indx);
                }
            }

            if (tomato_x < dim_size[0] - 1)
            {
                const auto next_indx = cur_indx + 1;
                if (tomato_state[next_indx] == 0)
                {
                    tomato_state[next_indx] = 1;
                    next.push_back(next_indx);
                }
            }

            if (tomato_y != 0)
            {
                const auto next_indx = cur_indx - dim_size[0];
                if (tomato_state[next_indx] == 0)
                {
                    tomato_state[next_indx] = 1;
                    next.push_back(next_indx);
                }
            }

            if (tomato_y < dim_size[1] - 1)
            {
                const auto next_indx = cur_indx + dim_size[0];
                if (tomato_state[next_indx] == 0)
                {
                    tomato_state[next_indx] = 1;
                    next.push_back(next_indx);
                }
            }
        }

        if (!next.empty())
        {
            day++;
        }
        std::swap(current, next);
    }

    auto fresh_tomato = std::find(tomato_state.begin(), tomato_state.end(), 0);
    if (fresh_tomato == tomato_state.end())
    {
        cout << day << endl;
    }
    else
    {
        cout << "-1" << endl;
    }

    return 0;
}