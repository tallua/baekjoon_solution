#include <iostream>
#include <vector>
#include <limits>

using namespace std;

enum class direction
{
    Right = 1,
    Left = 2,
    Up = 3,
    Down = 4
};

enum class cell_type
{
    W = 0,
    R = 1,
    B = 2
};

struct Cell
{
    cell_type type;

    vector<size_t> pawns;
};

struct Pawn
{
    direction dir;
    size_t x, y;
};

struct Board
{
private:
    const size_t _N;

    vector<vector<Cell>> _cells;
    vector<Pawn> _pawns;

public:
    Board(const vector<vector<Cell>>& cells, const vector<Pawn>& pawns)
        : _N(cells.size()), _cells(cells), _pawns(pawns)
    {
        for (size_t p = 0; p < pawns.size(); ++p)
        {
            _cells[pawns[p].y][pawns[p].x].pawns.push_back(p);
        }
    }

    bool simulate()
    {
        for (size_t p = 0; p < _pawns.size(); ++p)
        {
            _simulate_pawn(p);
            if (_cells[_pawns[p].y][_pawns[p].x].pawns.size() >= 4)
                return false;
        }

        return true;
    }

    void print()
    {
        for (size_t y = 0; y < _N; ++y)
        {
            for (size_t x = 0; x < _N; ++x)
            {
                cout << _cells[y][x].pawns.size() << ' ';
            }

            cout << endl;
        }
    }

private:
    void _simulate_pawn(size_t index)
    {
        size_t next_x = _pawns[index].x;
        size_t next_y = _pawns[index].y;
        direction next_dir = _pawns[index].dir;
        bool is_blue = false;

        switch (_pawns[index].dir)
        {
        case direction::Up:
            is_blue = next_y == 0 || _cells[next_y - 1][next_x].type == cell_type::B;
            if (is_blue)
            {
                next_dir = direction::Down;
                next_y++;
            }
            else
            {
                next_y--;
            }
            break;
        case direction::Down:
            is_blue = next_y == _N - 1 || _cells[next_y + 1][next_x].type == cell_type::B;
            if (is_blue)
            {
                next_dir = direction::Up;
                next_y--;
            }
            else
            {
                next_y++;
            }
            break;
        case direction::Left:
            is_blue = next_x == 0 || _cells[next_y][next_x - 1].type == cell_type::B;
            if (is_blue)
            {
                next_dir = direction::Right;
                next_x++;
            }
            else
            {
                next_x--;
            }
            break;
        case direction::Right:
            is_blue = next_x == _N - 1 || _cells[next_y][next_x + 1].type == cell_type::B;
            if (is_blue)
            {
                next_dir = direction::Left;
                next_x--;
            }
            else
            {
                next_x++;
            }
            break;
        }
        _pawns[index].dir = next_dir;

        if (next_x == numeric_limits<size_t>::max() || next_x == _N ||
            next_y == numeric_limits<size_t>::max() || next_y == _N ||
            _cells[next_y][next_x].type == cell_type::B)
        {
            _pawns[index].dir = next_dir;
        }
        else if(_cells[next_y][next_x].type == cell_type::W)
        {
            auto& current_pawns = _cells[_pawns[index].y][_pawns[index].x].pawns;
            auto& next_pawns = _cells[next_y][next_x].pawns;

            size_t x1 = 0;
            while (x1 < current_pawns.size() && current_pawns[x1] != index)
            {
                ++x1;
            }

            size_t x2 = x1;
            while (x2 < current_pawns.size())
            {
                _pawns[current_pawns[x2]].y = next_y;
                _pawns[current_pawns[x2]].x = next_x;
                next_pawns.push_back(current_pawns[x2]);
                ++x2;
            }

            current_pawns.resize(x1);
        }
        else
        {
            auto& current_pawns = _cells[_pawns[index].y][_pawns[index].x].pawns;
            auto& next_pawns = _cells[next_y][next_x].pawns;

            size_t x1 = 0;
            while (x1 < current_pawns.size() && current_pawns[x1] != index)
            {
                ++x1;
            }

            size_t x2 = current_pawns.size() - 1;
            while (x2 >= x1)
            {
                _pawns[current_pawns[x2]].y = next_y;
                _pawns[current_pawns[x2]].x = next_x;
                next_pawns.push_back(current_pawns[x2]);

                if (x2 == 0)
                    break;
                --x2;
            }

            current_pawns.resize(x1);
        }
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    vector<vector<Cell>> cells;
    cells.resize(N);
    for (size_t y = 0; y < N; ++y)
    {
        cells[y].resize(N);
        for (size_t x = 0; x < N; ++x)
        {
            int type;
            cin >> type;
            cells[y][x].type = static_cast<cell_type>(type);
        }
    }

    vector<Pawn> pawns;
    pawns.resize(K);

    for (size_t k = 0; k < K; ++k)
    {
        int dir;
        cin >> pawns[k].y >> pawns[k].x >> dir;
        pawns[k].y--;
        pawns[k].x--;
        pawns[k].dir = static_cast<direction>(dir);
    }

    Board board(cells, pawns);

    bool complete = true;
    int count = 0;
    do
    {
        //cout << "----" << count << "----" << endl;
        //board.print();
        count++;
        if (count >= 1000)
        {
            complete = false;
        }
    } while (board.simulate() && complete);

    if (complete)
    {
        cout << count << '\n';
    }
    else
    {
        cout << "-1\n";
    }

    return 0;
}