#include <iostream>
#include <vector>

using namespace std;

void solve_odd(int R, int C, vector<char> &result)
{
    if (R % 2 == 0)
    {
        for (int c = 0; c < C - 2; c += 2)
        {
            for (int r = 0; r < R - 1; ++r)
            {
                result.push_back('D');
            }
            result.push_back('R');
            for (int r = 0; r < R - 1; ++r)
            {
                result.push_back('U');
            }
            result.push_back('R');
        }
        for (int r = 0; r < R - 1; ++r)
        {
            result.push_back('D');
        }
    }
    else
    {
        for (int r = 0; r < R - 2; r += 2)
        {
            for (int c = 0; c < C - 1; ++c)
            {
                result.push_back('R');
            }
            result.push_back('D');
            for (int c = 0; c < C - 1; ++c)
            {
                result.push_back('L');
            }
            result.push_back('D');
        }
        for (int c = 0; c < C - 1; ++c)
        {
            result.push_back('R');
        }
    }
}

void solve(const vector<vector<int>> &map, vector<char> &result)
{
    const int R = map.size();
    const int C = map[0].size();

    if (R % 2 == 0 && C % 2 == 0)
    {
        int min_val = 10000000;
        int min_r;
        int min_c;
        for (int r = 0; r < R; ++r)
        {
            for (int c = (r + 1) % 2; c < C; c += 2)
            {
                if (map[r][c] < min_val)
                {
                    min_val = map[r][c];
                    min_r = r;
                    min_c = c;
                }
            }
        }

        if (min_r % 2 == 0)
        {
            // sector 1
            for (int r = 0; r < min_r; r += 2)
            {
                for (int c = 0; c < C - 1; ++c)
                {
                    result.push_back('R');
                }
                result.push_back('D');
                for (int c = 0; c < C - 1; ++c)
                {
                    result.push_back('L');
                }
                result.push_back('D');
            }
            // sector 2
            for (int c = 0; c < min_c - 1; c += 2)
            {
                for (int r = min_r; r < R - 1; ++r)
                {
                    result.push_back('D');
                }
                result.push_back('R');
                for (int r = min_r; r < R - 1; ++r)
                {
                    result.push_back('U');
                }
                result.push_back('R');
            }
            // sector 3
            result.push_back('D');
            result.push_back('R');
            for (int r = min_r + 1; r < R - 1; r += 2)
            {
                result.push_back('D');
                result.push_back('L');
                result.push_back('D');
                result.push_back('R');
            }

            for (int c = min_c; c < C - 1; c += 2)
            {
                result.push_back('R');
                for (int r = min_r + 1; r < R; ++r)
                {
                    result.push_back('U');
                }
                result.push_back('R');
                for (int r = min_r + 1; r < R; ++r)
                {
                    result.push_back('D');
                }
            }
        }
        else
        {
            // sector 1
            for (int c = 0; c < min_c; c += 2)
            {
                for (int r = 0; r < R - 1; ++r)
                {
                    result.push_back('D');
                }
                result.push_back('R');
                for (int r = 0; r < R - 1; ++r)
                {
                    result.push_back('U');
                }
                result.push_back('R');
            }
            // sector 2
            for (int r = 0; r < min_r - 1; r += 2)
            {
                for (int c = min_c; c < C - 1; ++c)
                {
                    result.push_back('R');
                }
                result.push_back('D');
                for (int c = min_c; c < C - 1; ++c)
                {
                    result.push_back('L');
                }
                result.push_back('D');
            }
            // sector 3
            result.push_back('R');
            result.push_back('D');
            for (int c = min_c + 1; c < C - 1; c += 2)
            {
                result.push_back('R');
                result.push_back('U');
                result.push_back('R');
                result.push_back('D');
            }

            for (int r = min_r; r < R - 1; r += 2)
            {
                result.push_back('D');
                for (int c = min_c + 1; c < C; ++c)
                {
                    result.push_back('L');
                }
                result.push_back('D');
                for (int c = min_c + 1; c < C; ++c)
                {
                    result.push_back('R');
                }
            }
        }
    }
    else
    {
        solve_odd(R, C, result);
    }
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int R, C;
    cin >> R >> C;

    vector<vector<int>> map;
    map.resize(R);
    for (auto &r : map)
        r.resize(C);

    for (int r = 0; r < R; ++r)
    {
        for (int c = 0; c < C; ++c)
        {
            cin >> map[r][c];
        }
    }

    vector<char> result;
    result.reserve(R * C + 1);

    solve(map, result);

    result.push_back(0);
    cout << result.data() << endl;

    return 0;
}