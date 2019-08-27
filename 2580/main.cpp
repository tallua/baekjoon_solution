#include <iostream>
#include <array>
#include <vector>


using namespace std;


using board_t = array<array<int, 9>, 9>;
using point_t = array<int, 2>;


array<bool, 9> getAvailables(const board_t& board, const point_t& point)
{
    array<bool, 9> available;
    available.fill(true);

    // check horizontal
    for(int x = 0; x < board.size(); ++x)
    {
        int val = board[x][point[1]];
        if(x == point[0])
        {
            continue;
        }
        else if (val != 0)
        {
            available[val - 1] = false;
        }
    }
    // check vertical
    for(int y = 0; y < board[0].size(); ++y)
    {
        int val = board[point[0]][y];
        if(y == point[1])
        {
            continue;
        }
        else if (val != 0)
        {
            available[val - 1] = false;
        }
    }
    // check square
    int sqr_offset_x = (point[0] / 3) * 3;
    int sqr_offset_y = (point[1] / 3) * 3;
    for(int x = 0; x < 3; ++x)
    {
        for(int y = 0; y < 3; ++y)
        {
            int val = board[x + sqr_offset_x][y + sqr_offset_y];
            if((x == point[0]) && (y == point[1]))
            {
                continue;
            }
            else if(val != 0)
            {
                available[val - 1] = false;
            }
        }
    }
    return available;
}


bool solve_recursive(board_t& board, vector<point_t>& points);
bool solve_dfs(board_t& board, vector<point_t>& points);


bool solve_dfs(board_t& board, vector<point_t>& points)
{
    if(points.size() == 0)
        return true;

    point_t point = points.back();
    array<bool, 9> availables = getAvailables(board, point);

    for(int i = 0; i < availables.size(); ++i)
    {
        if(availables[i])
        {
            board_t new_board = board;
            vector<point_t> new_points = points;
            new_board[point[0]][point[1]] = i + 1;
            new_points.pop_back();

            if(solve_recursive(new_board, new_points))
            {
                board = new_board;
                points = new_points;
                return true;
            }
        }
    }

    return false;    
}

bool solve_recursive(board_t& board, vector<point_t>& points)
{
    if(points.size() == 0)
        return true;

    bool notsolved = true;
    
    for(auto p_it = points.begin(); p_it != points.end();)
    {
        auto available = getAvailables(board, *p_it);

        // set val
        int cnt = 0;
        int indx = 0;
        for(int i = 0; i < available.size(); ++i)
        {
            if(available[i] == true)
            {
                cnt++;
                indx = i;
            }
        }

        if(cnt == 1)
        {
            notsolved = false;
            board[p_it->at(0)][p_it->at(1)] = indx + 1;
            p_it = points.erase(p_it);
        }
        else
        {
            ++p_it;
        }
    }

    if(notsolved)
    {
        return solve_dfs(board, points);
    }
    else
    {
        return solve_recursive(board, points);
    }
}


int main(int argc, char** argv)
{
    board_t board;
    vector<point_t> points;
    for(int x = 0; x < board.size(); ++x)
    {
        for(int y = 0; y < board[0].size(); ++y)
        {
            cin >> board[x][y];
            if(board[x][y] == 0)
            {
                points.push_back({x, y});
            }
        }
    }

    solve_recursive(board, points);

    for(int x = 0; x < board.size(); ++x)
    {
        bool first = true;
        for(int y = 0; y < board[0].size(); ++y)
        {
            if(!first)
                cout << " ";
            first = false;
            cout << board[x][y];
        }
        cout << '\n';
    }

    return 0;
}