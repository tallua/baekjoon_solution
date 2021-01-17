#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <algorithm>

using namespace std;
using coord_t = int;

enum Direction
{
    U,
    D,
    L,
    R
};

int main(int argc, char **argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N, Q;
    cin >> N >> Q;

    std::string seq;
    cin >> seq;

    coord_t init_x = 0;
    coord_t init_y = 0;
    array<int, 4> count = {0u, 0u, 0u, 0u};
    for (size_t n = 0; n < N; ++n)
    {
        switch (seq[n])
        {
        case 'U':
            init_y++;
            count[Direction::U]++;
            break;
        case 'D':
            init_y--;
            count[Direction::D]++;
            break;
        case 'L':
            init_x--;
            count[Direction::L]++;
            break;
        case 'R':
            init_x++;
            count[Direction::R]++;
            break;
        }
    }

    for (size_t q = 0; q < Q; ++q)
    {
        coord_t end_x, end_y;
        cin >> end_x >> end_y;

        coord_t dist_from_origin = abs(end_x) + abs(end_y);
        coord_t diff_x = end_x - init_x;
        coord_t diff_y = end_y - init_y;

        if ((abs(diff_x) + abs(diff_y)) % 2 != 0 || dist_from_origin > N)
        {
            cout << "-1\n";
            continue;
        }

        auto current_count = count;

        if (end_x < 0)
            current_count[Direction::L] += end_x;
        else
            current_count[Direction::R] -= end_x;

        if (end_y < 0)
            current_count[Direction::D] += end_y;
        else
            current_count[Direction::U] -= end_y;

        if (current_count[Direction::L] > 0 && current_count[Direction::R] > 0)
        {
            int min_count = min(current_count[Direction::L], current_count[Direction::R]);
            current_count[Direction::L] -= min_count;
            current_count[Direction::R] -= min_count;
        }

        if (current_count[Direction::U] > 0 && current_count[Direction::D] > 0)
        {
            int min_count = min(current_count[Direction::U], current_count[Direction::D]);
            current_count[Direction::U] -= min_count;
            current_count[Direction::D] -= min_count;
        }

        int minus_count =
            (current_count[Direction::U] < 0 ? -current_count[Direction::U] : 0) +
            (current_count[Direction::D] < 0 ? -current_count[Direction::D] : 0) +
            (current_count[Direction::L] < 0 ? -current_count[Direction::L] : 0) +
            (current_count[Direction::R] < 0 ? -current_count[Direction::R] : 0);

        int plus_count =
            (current_count[Direction::U] > 0 ? current_count[Direction::U] : 0) +
            (current_count[Direction::D] > 0 ? current_count[Direction::D] : 0) +
            (current_count[Direction::L] > 0 ? current_count[Direction::L] : 0) +
            (current_count[Direction::R] > 0 ? current_count[Direction::R] : 0);

        int total_count = minus_count + (minus_count > plus_count ? 0 : (plus_count - minus_count) / 2);
        cout << total_count << '\n';
    }

    return 0;
}