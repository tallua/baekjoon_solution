#include <iostream>
#include <vector>

using namespace std;

void fill_line(int line_length, const char movement, vector<char> &result)
{
    for (int i = 0; i < line_length - 1; ++i)
    {
        result.push_back(movement);
    }
}

void solve(const int R, const int C, vector<char> &result, int min_r, int min_c)
{
    if (R % 2 == 0 && C % 2 == 0 && min_r % 2 == 0)
    {
        // sector 1
        for (int r = 0; r < min_r; r += 2)
        {
            fill_line(C, 'R', result);
            result.push_back('D');
            fill_line(C, 'L', result);
            result.push_back('D');
        }
        // sector 2
        for (int c = 0; c < min_c - 1; c += 2)
        {
            fill_line(R - min_r, 'D', result);
            result.push_back('R');
            fill_line(R - min_r, 'U', result);
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
            fill_line(R - min_r, 'U', result);
            result.push_back('R');
            fill_line(R - min_r, 'D', result);
        }
    }
    else if (R % 2 == 0 && C % 2 == 0)
    {
        // sector 1
        for (int c = 0; c < min_c; c += 2)
        {
            fill_line(R, 'D', result);
            result.push_back('R');
            fill_line(R, 'U', result);
            result.push_back('R');
        }
        // sector 2
        for (int r = 0; r < min_r - 1; r += 2)
        {
            fill_line(C - min_c, 'R', result);
            result.push_back('D');
            fill_line(C - min_c, 'L', result);
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
            fill_line(C - min_c, 'L', result);
            result.push_back('D');
            fill_line(C - min_c, 'R', result);
        }
    }
    else if (R % 2 == 0)
    {
        for (int c = 0; c < C - 2; c += 2)
        {
            fill_line(R, 'D', result);
            result.push_back('R');
            fill_line(R, 'U', result);
            result.push_back('R');
        }
        fill_line(R, 'D', result);
    }
    else
    {
        for (int r = 0; r < R - 2; r += 2)
        {
            fill_line(C, 'R', result);
            result.push_back('D');
            fill_line(C, 'L', result);
            result.push_back('D');
        }
        fill_line(C, 'R', result);
    }
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int R, C;
    cin >> R >> C;

    int min_val = 10000000;
    int min_r, min_c;

    for (int r = 0; r < R; ++r)
    {
        for (int c = 0; c < C; ++c)
        {
            int tmp;
            cin >> tmp;
            if ((r + c) % 2 == 1 && tmp < min_val)
            {
                min_val = tmp;
                min_r = r;
                min_c = c;
            }
        }
    }

    vector<char> result;
    result.reserve(R * C + 1);

    solve(R, C, result, min_r, min_c);

    result.push_back(0);
    cout << result.data() << endl;

    return 0;
}