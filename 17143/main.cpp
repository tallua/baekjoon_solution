#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct shark_t
{
    bool valid = true;
    int x, y;
    int speed, dir, size;
};

template <typename T>
constexpr T mymod(T val, T mod)
{
    return (val + (val / mod + 1) * mod) % mod;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int R, C;
    cin >> R >> C;

    int M;
    cin >> M;

    vector<shark_t> sharks;
    sharks.resize(M);
    int target_id = -1;
    int target_y = R;
    for (int m = 0; m < M; ++m)
    {
        sharks[m].valid = true;
        cin >> sharks[m].y >> sharks[m].x;
        cin >> sharks[m].speed >> sharks[m].dir >> sharks[m].size;

        sharks[m].x--;
        sharks[m].y--;

        if (sharks[m].x == 0)
        {
            if (sharks[m].y < target_y)
            {
                target_id = m;
                target_y = sharks[m].y;
            }
        }
    }

    // simulate
    vector<vector<int>> board;
    board.resize(R);
    for (auto& r : board)
        r.resize(C, -1);

    int size_sum = 0;
    for (int x = 0; x < C; ++x)
    {
        // capture shark
        if (target_id != -1)
        {
            size_sum = sharks[target_id].size;
            sharks[target_id].valid = false;
        }

        // clear board
        for (auto& r : board)
            for (auto& c : r)
                c = -1;

        // move sharks
        target_id = -1;
        target_y = R;
        for (int m = 0; m < M; ++m)
        {
            if (!sharks[m].valid)
                continue;

            // next pos of shark
            {
                int mod;
                int next_dir;
                switch (sharks[m].dir)
                {
                case 1:
                    sharks[m].y -= sharks[m].speed;
                    mod = (R - 1) * 2;
                    sharks[m].y = mymod(sharks[m].y, mod);
                    if (sharks[m].y > (R - 1))
                    {
                        sharks[m].y = mod - sharks[m].y;
                        sharks[m].dir = 1;
                    }
                    else
                    {
                        sharks[m].dir = 2;
                    }

                    break;
                case 2:
                    sharks[m].y += sharks[m].speed;
                    mod = (R - 1) * 2;
                    sharks[m].y = mymod(sharks[m].y, mod);
                    if (sharks[m].y > (R - 1))
                    {
                        sharks[m].y = mod - sharks[m].y;
                        sharks[m].dir = 1;
                    }
                    else
                    {
                        sharks[m].dir = 2;
                    }
                    break;
                case 3:
                    sharks[m].x += sharks[m].speed;
                    mod = (C - 1) * 2;
                    sharks[m].x = mymod(sharks[m].x, mod);
                    if (sharks[m].x > (C - 1))
                    {
                        sharks[m].x = mod - sharks[m].x;
                        sharks[m].dir = 4;
                    }
                    else
                    {
                        sharks[m].dir = 3;
                    }
                    break;
                case 4:
                    sharks[m].x -= sharks[m].speed;
                    mod = (C - 1) * 2;
                    sharks[m].x = mymod(sharks[m].x, mod);
                    if (sharks[m].x > (C - 1))
                    {
                        sharks[m].x = mod - sharks[m].x;
                        sharks[m].dir = 4;
                    }
                    else
                    {
                        sharks[m].dir = 3;
                    }
                    break;
                }
            }

            // move shark
            int shark_at_board = board[sharks[m].y][sharks[m].x];
            if (shark_at_board == -1)
            {
                board[sharks[m].y][sharks[m].x] = m;
            }
            else
            {
                if (sharks[m].size > sharks[shark_at_board].size)
                {
                    board[sharks[m].y][sharks[m].x] = m;
                    sharks[shark_at_board].valid = false;
                }
                else
                {
                    sharks[m].valid = false;
                }
            }

            if (sharks[m].x == x + 1 && sharks[m].y <= target_y)
            {
                target_id = board[sharks[m].y][sharks[m].x];
                target_y = sharks[m].y;
            }
        }

        for (int y = 0; y < R; ++y)
        {
            for (int x = 0; x < C; ++x)
            {
                cout << board[y][x] << ' ';
            }
            cout << endl;
        }
    }

    cout << size_sum << endl;

    return 0;
}