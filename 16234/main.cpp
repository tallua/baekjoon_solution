#include <iostream>
#include <vector>
#include <array>
#include <limits>

using namespace std;
using people_t = int;
using group_t = size_t;

#define MAX_N 50

template <typename _T>
using board_t = array<_T, MAX_N * MAX_N>;

constexpr people_t calc_diff(const people_t& lhs, const people_t& rhs) { return lhs > rhs ? lhs - rhs : rhs - lhs; }

size_t N;
board_t<people_t> peoples;

people_t L, R;

board_t<group_t> groups;


void fill(size_t x, size_t y, people_t& people_count, size_t& group_count)
{
    if(y > 0 && groups[MAX_N * (y - 1) + x] == numeric_limits<group_t>::max())
    {
        people_t diff = calc_diff(peoples[MAX_N * y + x], peoples[MAX_N * (y - 1) + x]);
        if(L <= diff && diff <= R)
        {
            groups[MAX_N * (y - 1) + x] = groups[MAX_N * y + x];
            people_count += peoples[MAX_N * (y - 1) + x];
            group_count++;

            fill(x, y - 1, people_count, group_count);
        }
    }

    if(y < N - 1 && groups[MAX_N * (y + 1) + x] == numeric_limits<group_t>::max())
    {
        people_t diff = calc_diff(peoples[MAX_N * y + x], peoples[MAX_N * (y + 1) + x]);
        if(L <= diff && diff <= R)
        {
            groups[MAX_N * (y + 1) + x] = groups[MAX_N * y + x];
            people_count += peoples[MAX_N * (y + 1) + x];
            group_count++;

            fill(x, y + 1, people_count, group_count);
        }
    }
    
    if(x > 0 && groups[MAX_N * y + x - 1] == numeric_limits<group_t>::max())
    {
        people_t diff = calc_diff(peoples[MAX_N * y + x], peoples[MAX_N * y + x - 1]);
        if(L <= diff && diff <= R)
        {
            groups[MAX_N * y + x - 1] = groups[MAX_N * y + x];
            people_count += peoples[MAX_N * y + x - 1];
            group_count++;

            fill(x - 1, y, people_count, group_count);
        }
    }

    if(x < N - 1 && groups[MAX_N * y + x + 1] == numeric_limits<group_t>::max())
    {
        people_t diff = calc_diff(peoples[MAX_N * y + x], peoples[MAX_N * y + x + 1]);
        if(L <= diff && diff <= R)
        {
            groups[MAX_N * y + x + 1] = groups[MAX_N * y + x];
            people_count += peoples[MAX_N * y + x + 1];
            group_count++;

            fill(x + 1, y, people_count, group_count);
        }
    }
}

bool step()
{
    groups.fill(numeric_limits<group_t>::max());

    vector<people_t> group_meta;
    for(size_t y = 0; y < N; ++y)
    {
        for(size_t x = 0; x < N; ++x)
        {
            if(groups[MAX_N * y + x] == numeric_limits<group_t>::max())
            {
                groups[MAX_N * y + x] = group_meta.size();
                people_t people_cnt = peoples[MAX_N * y + x];
                size_t group_cnt = 1;

                fill(x, y, people_cnt, group_cnt);

                group_meta.push_back(people_cnt / group_cnt);
            }
        }
    }

    // debug
    //for(size_t y = 0; y < N; ++y)
    //{
    //    for(size_t x = 0; x < N; ++x)
    //    {
    //        cout << groups[y][x] << ':' << peoples[y][x] << ' ';
    //    }
    //
    //    cout << endl;
    //}
    //cout << endl;
    // debug end

    if(group_meta.size() == N * N)
        return false;
    
    for(size_t y = 0; y < N; ++y)
    {
        for(size_t x = 0; x < N; ++x)
        {
            peoples[MAX_N * y + x] = group_meta[groups[MAX_N * y + x]];
        }
    }
    
    return true;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N >> L >> R;

    for(size_t y = 0; y < N; ++y)
    {
        for(size_t x = 0; x < N; ++x)
        {
            cin >> peoples[MAX_N * y + x];
        }
    }

    size_t count = 0;
    while(step())
    {
        count++;
    }
    cout << count << '\n';

    return 0;
}