#include <iostream>
#include <vector>
#include <functional>

using namespace std;

using board_t = vector<vector<int>>;
struct pos_t { int x, y; };
using step_func = function<bool(pos_t&)>;

int find_max(const board_t& b) 
{
    int max_val = b[0][0];
    for(auto& row  : b) 
        for(auto& val : row) 
            max_val = max(max_val, val);
    return max_val;
};

board_t step_board(board_t board, pos_t init, const step_func& step1, const step_func& step2)
{
    int N = board.size();
    do {
        pos_t write = init;
        pos_t read = init;
        int val = 0;
        do{
            if(val == 0)
                val = board[read.y][read.x];
            else if(board[read.y][read.x] == 0)
            {
                // do nothing
            }
            else if(val == board[read.y][read.x])
            {
                board[write.y][write.x] = val << 1;
                step2(write);
                val = 0;
            }
            else if(val != board[read.y][read.x])
            {
                board[write.y][write.x] = val;
                step2(write);
                val = board[read.y][read.x];
            }
        }while(step2(read));

        board[write.y][write.x] = val;
        
        while(step2(write))
        {
            board[write.y][write.x] = 0;
        }
    } while(step1(init));

    return board;
}

int traverse(const board_t& board, int depth)
{
    if(depth == 5)
        return find_max(board);

    const int N = board.size();
    int max_val = 0;

    const step_func inc_x = [N](pos_t& p) -> bool { p.x++; return p.x >= N ? false : true; };
    const step_func dec_x = [N](pos_t& p) -> bool { p.x--; return p.x < 0 ? false : true; };
    const step_func inc_y = [N](pos_t& p) -> bool { p.y++; return p.y >= N ? false : true; };
    const step_func dec_y = [N](pos_t& p) -> bool { p.y--; return p.y < 0 ? false : true; };

    // collapse left
    board_t left = step_board(board, { 0, 0 }, inc_y, inc_x);
    max_val = max(max_val, traverse(left, depth + 1));
    board_t right = step_board(board, { N - 1, 0 }, inc_y, dec_x);
    max_val = max(max_val, traverse(right, depth + 1));
    board_t up = step_board(board, { 0, 0 }, inc_x, inc_y);
    max_val = max(max_val, traverse(up, depth + 1));
    board_t down = step_board(board, { 0, N - 1 }, inc_x, dec_y);
    max_val = max(max_val, traverse(down, depth + 1));

    return max_val;
}

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    board_t board;
    board.resize(N);
    for(auto& row : board) row.resize(N, 0);

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cin >> board[i][j];
        }
    }

    cout << traverse(board, 0) << endl;

    return 0;
}

