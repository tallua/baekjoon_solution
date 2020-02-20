#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int solve(const vector<array<int, 2>>& enemies, int N, int W, array<int, 3> init, size_t last)
{
    array<int, 3> current;
    array<int, 3> next;
    int last_zero = 0;

    current = init;

    for (int n = 1; n < N; ++n)
    {
        bool can_combine_each = enemies[n][0] + enemies[n][1] <= W;
        bool can_combine_0 = enemies[n - 1][0] + enemies[n][0] <= W;
        bool can_combine_1 = enemies[n - 1][1] + enemies[n][1] <= W;

        auto check = [](int& target, int val)
        {
            target = min(target, val);
        };


        if (n == 1 && last != 0)
        {
            next[0] = 3;
            next[1] = 2;
            next[2] = 2;

            if (can_combine_each)
            {
                check(next[0], current[1] + 1);
                check(next[0], current[2] + 1);
            }

            if (can_combine_0 && last != 2)
            {
                check(next[1], current[1]);
            }

            if (can_combine_1 && last != 1)
            {
                check(next[2], current[2]);
            }

        }
        else
        {
            next[0] = current[0] + 2;
            next[1] = current[0] + 1;
            next[2] = current[0] + 1;

            if (can_combine_0)
            {
                check(next[0], current[2] + 2);
                check(next[1], current[2] + 1);
            }
            else
            {
                check(next[0], current[2] + 3);
                check(next[1], current[2] + 2);
            }

            if (can_combine_1)
            {
                check(next[0], current[1] + 2);
                check(next[2], current[1] + 1);
            }
            else
            {
                check(next[0], current[1] + 3);
                check(next[2], current[1] + 2);
            }

            if (can_combine_each)
            {
                check(next[0], current[0] + 1);
                check(next[0], current[2] + 2);
                check(next[0], current[1] + 2);
            }

            if (can_combine_0 && can_combine_1)
            {
                check(next[0], last_zero + 2);
            }
        }

        last_zero = current[0];
        std::swap(current, next);
    }

    return current[last];
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--)
    {
        int N, W;
        cin >> N >> W;

        vector<array<int, 2>> enemies;
        enemies.resize(N);

        for (int n = 0; n < N; ++n)
        {
            cin >> enemies[n][0];
        }
        for (int n = 0; n < N; ++n)
        {
            cin >> enemies[n][1];
        }

        int result = solve(enemies, N, W, { enemies[0][0] + enemies[0][1] <= W ? 1 : 2, 1, 1 }, 0);

        if (enemies[N - 1][0] + enemies[0][0] <= W)
        {
            int tmp = solve(enemies, N, W, { N * 2, N * 2, 1 }, 2) + 1;
            result = min(result, tmp);
        }
        if (enemies[N - 1][1] + enemies[0][1] <= W)
        {
            int tmp = solve(enemies, N, W, { N * 2, 1, N * 2 }, 1) + 1;
            result = min(result, tmp);
        }

        cout << result << endl;
    }

    return 0;
}