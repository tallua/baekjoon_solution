#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

#define DIM_SIZE 11

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    // dimension info
    array<int, DIM_SIZE> dim_size;
    for (int dim_indx = 0; dim_indx < dim_size.size(); ++dim_indx)
    {
        cin >> dim_size[dim_indx];
    }

    array<int, DIM_SIZE> dim_hop;
    dim_hop[0] = 1;
    for (int dim_indx = 0; dim_indx < dim_size.size() - 1; ++dim_indx)
    {
        dim_hop[dim_indx + 1] = dim_hop[dim_indx] * dim_size[dim_indx];
    }

    // tomato info
    vector<int> tomato_state;
    vector<int> current;
    tomato_state.resize(dim_hop.back() * dim_size.back());
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

            // find next index
            for (int dim_indx = 0; dim_indx < dim_size.size(); ++dim_indx)
            {
                int tomato_indx = (cur_indx / dim_hop[dim_indx]) % dim_size[dim_indx];

                if (tomato_indx != 0)
                {
                    const auto next_indx = cur_indx - dim_hop[dim_indx];
                    if (tomato_state[next_indx] == 0)
                    {
                        tomato_state[next_indx] = 1;
                        next.push_back(next_indx);
                    }
                }

                if (tomato_indx < dim_size[dim_indx] - 1)
                {
                    const auto next_indx = cur_indx + dim_hop[dim_indx];
                    if (tomato_state[next_indx] == 0)
                    {
                        tomato_state[next_indx] = 1;
                        next.push_back(next_indx);
                    }
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