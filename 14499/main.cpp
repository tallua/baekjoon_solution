#include <iostream>
#include <vector>
#include <array>

using namespace std;

using val_t = int;
using board_t = vector<vector<val_t>>;

enum direction
{
    EAST = 0,
    WEST = 1,
    NORTH = 2,
    SOUTH = 3
};

//   1
// 3 0 2
//   4
//   5
struct Cube
{
    int x, y;

    const static size_t next_side[4][6];

    array<val_t, 6> cube = {
        0,
    };

    val_t get_top() const { return cube[0]; }
    val_t get_bottom() const { return cube[5]; }
    void set_bottom(val_t val) { cube[5] = val; }

    void rotate(direction dir)
    {
        array<val_t, 6> next_cube;

        for (size_t i = 0; i < 6; ++i)
        {
            next_cube[i] = cube[next_side[dir][i]];
        }

        for (size_t i = 0; i < 6; ++i)
        {
            cube[i] = next_cube[i];
        }
    }
};

const size_t Cube::next_side[4][6]{
    {3, 1, 0, 5, 4, 2}, // E
    {2, 1, 5, 0, 4, 3}, // W
    {4, 0, 2, 3, 5, 1}, // N
    {1, 5, 2, 3, 0, 4}  // S
};

bool move_cube(board_t& board, Cube& cube, direction dir)
{
    bool discard = true;
    int next_x = cube.x;
    int next_y = cube.y;
    switch (dir)
    {
    case EAST:
        if (next_x < board[0].size() - 1)
        {
            next_x += 1;
            discard = false;
        }
        break;
    case WEST:
        if (next_x > 0)
        {
            next_x -= 1;
            discard = false;
        }
        break;
    case NORTH:
        if (next_y > 0)
        {
            next_y -= 1;
            discard = false;
        }
        break;
    case SOUTH:
        if (next_y < board.size() - 1)
        {
            next_y += 1;
            discard = false;
        }
        break;
    }

    if (discard)
        return false;

    cube.x = next_x;
    cube.y = next_y;
    cube.rotate(dir);

    if (board[next_y][next_x] == 0)
    {
        board[next_y][next_x] = cube.get_bottom();
    }
    else
    {
        cube.set_bottom(board[next_y][next_x]);
        board[next_y][next_x] = 0;
    }

    //for (auto& r : board)
    //{
    //    for (auto& v : r)
    //    {
    //        cout << v << ' ';
    //    }
    //    cout << endl;
    //}
    //cout << endl;
    //
    //for (size_t i = 0; i < 6; ++i)
    //{
    //    cout << cube.cube[i] << ' ';
    //}
    //cout << endl;

    return true;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, start_x, start_y, K;
    cin >> N >> M >> start_x >> start_y >> K;

    board_t board;
    board.resize(N);
    for (int n = 0; n < N; ++n)
    {
        board[n].resize(M);
        for (int m = 0; m < M; ++m)
        {
            cin >> board[n][m];
        }
    }

    Cube cube;
    cube.x = start_y;
    cube.y = start_x;

    while (K--)
    {
        int dir;
        cin >> dir;
        if (move_cube(board, cube, static_cast<direction>(dir - 1)))
        {
            cout << cube.get_top() << '\n';
        }
    }

    cout << endl;

    return 0;
}