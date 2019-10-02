#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct pos_t
{
    int x, y;
};
struct state_t
{
    const vector<vector<char>>& board;
    pos_t r;
    pos_t b;
};

vector<bool> step_board(state_t& current, pos_t* first, pos_t* second, const function<pos_t(pos_t)>& step, const int M, const int N)
{
    vector<bool> result;
    result.resize(2, false);
    
    while(first->x > 0 && first->y > 0 && first->x < M - 1 && first->y < N - 1)
    {
        const pos_t next_first = step(*first);
        const char val = current.board[next_first.y][next_first.x];
        if(val == '#')
        {
            break;
        }
        else if(val == '.')
        {
            *first = next_first;
        }
        else if(val == 'O')
        {
            *first = next_first;
            result[0] = true;
            break;
        }
    }

    while(second->x > 0 && second->y > 0 && second->x < M - 1 && second->y < N - 1)
    {
        const pos_t next_second = step(*second);
        const char val = current.board[next_second.y][next_second.x];
        if(val == '#')
        {
            break;
        }
        else if(val == '.' && first->x == next_second.x && first->y == next_second.y)
        {
            break;
        }
        else if(val == '.')
        {
            *second = next_second;
        }
        else if(val == 'O')
        {
            *second = next_second;
            result[1] = true;
            break;
        }
    }

    return result;
};

enum class dir_t
{
    up, down, right, left
};

int move_board(state_t& current, dir_t dir, int M, int N) 
{
    switch(dir)
    {
    case dir_t::up:
        {
            bool first_is_b = current.r.y > current.b.y ? true : false;
            pos_t* first = first_is_b ? &current.b : &current.r;
            pos_t* second = first_is_b ? &current.r : &current.b;
            auto step = [](const pos_t p) -> pos_t { return { .x = p.x, .y = p.y - 1 }; };
            auto next_r = step(current.r);
            auto next_b = step(current.b);
            if(current.board[next_r.y][next_r.x] == '#' &&
                current.board[next_b.y][next_b.x] == '#')
                return -1;
            
            vector<bool> result = step_board(current, first, second, step, M, N);
            if((first_is_b && result[0]) || (!first_is_b && result[1]))
                return -1;
            if((first_is_b && result[1]) || (!first_is_b && result[0]))
                return 1;
            return 0;
        }
        break;
    case dir_t::down:
        {
            bool first_is_b = current.r.y < current.b.y ? true : false;
            pos_t* first = first_is_b ? &current.b : &current.r;
            pos_t* second = first_is_b ? &current.r : &current.b;
            auto step = [](const pos_t p) -> pos_t { return { .x = p.x, .y = p.y + 1 }; };
            auto next_r = step(current.r);
            auto next_b = step(current.b);
            if(current.board[next_r.y][next_r.x] == '#' &&
                current.board[next_b.y][next_b.x] == '#')
                return -1;

            vector<bool> result = step_board(current, first, second, step, M, N);
            if((first_is_b && result[0]) || (!first_is_b && result[1]))
                return -1;
            if((first_is_b && result[1]) || (!first_is_b && result[0]))
                return 1;
            return 0;
        }
        break;
    case dir_t::right:
        {
            bool first_is_b = current.r.x < current.b.x ? true : false;
            pos_t* first = first_is_b ? &current.b : &current.r;
            pos_t* second = first_is_b ? &current.r : &current.b;
            auto step = [](const pos_t p) -> pos_t { return {.x = p.x + 1, .y = p.y }; };
            auto next_r = step(current.r);
            auto next_b = step(current.b);
            if(current.board[next_r.y][next_r.x] == '#' &&
                current.board[next_b.y][next_b.x] == '#')
                return -1;

            vector<bool> result = step_board(current, first, second, step, M, N);
            if((first_is_b && result[0]) || (!first_is_b && result[1]))
                return -1;
            if((first_is_b && result[1]) || (!first_is_b && result[0]))
                return 1;
            return 0;
        }
        break;
    case dir_t::left:
        {
            bool first_is_b = current.r.x > current.b.x ? true : false;
            pos_t* first = first_is_b ? &current.b : &current.r;
            pos_t* second = first_is_b ? &current.r : &current.b;
            auto step = [](const pos_t p) -> pos_t { return { .x = p.x - 1, .y = p.y }; };
            auto next_r = step(current.r);
            auto next_b = step(current.b);
            if(current.board[next_r.y][next_r.x] == '#' &&
                current.board[next_b.y][next_b.x] == '#')
                return -1;

            vector<bool> result = step_board(current, first, second, step, M, N);
            if((first_is_b && result[0]) || (!first_is_b && result[1]))
                return -1;
            if((first_is_b && result[1]) || (!first_is_b && result[0]))
                return 1;
            return 0;
        }
        break;
    }
};

int main(int argc, char** argv)
{

    int N, M;
    cin >> N >> M;

    vector<vector<char>> board;
    board.resize(N);
    for(auto& row : board) row.resize(M, '#');
    state_t init = { .board = board };

    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < M; ++x)
        {
            char val;
            cin >> val;
            switch(val)
            {
            case '#':
                break;
            case '.':
                board[y][x] = '.';
                break;
            case 'R':
                board[y][x] = '.';
                init.r = { .x=x, .y=y };
                break;
            case 'B':
                board[y][x] = '.';
                init.b = { .x=x, .y=y };
                break;
            case 'O':
                board[y][x] = 'O';
                break;
            }
        }
    }

    vector<state_t> current_tasks;
    vector<state_t> next_tasks;
    next_tasks.push_back(init);

    bool found = false;
    for(int depth = 0; depth < 10; ++depth)
    {
        if(found)
            break;

        swap(current_tasks, next_tasks);
        next_tasks.clear();

        for(state_t& current : current_tasks)
        {
            state_t up_state = current;
            int result = move_board(up_state, dir_t::up, M, N);
            if(result == 1)
            {
                found = true;
                break;            
            }
            else if(result == 0)
                next_tasks.push_back(up_state);
            state_t down_state = current;
            result = move_board(down_state, dir_t::down, M, N);
            if(result == 1)
            {
                found = true;
                break;            
            }
            else if(result == 0)
                next_tasks.push_back(down_state);
            state_t right_state = current;
            result = move_board(right_state, dir_t::right, M, N);
            if(result == 1)
            {
                found = true;
                break;            
            }
            else if(result == 0)
                next_tasks.push_back(right_state);
            state_t left_state = current;
            result = move_board(left_state, dir_t::left, M, N);
            if(result == 1)
            {
                found = true;
                break;            
            }
            else if(result == 0)
                next_tasks.push_back(left_state);
        }
        if(found)
        {
            cout << depth + 1 << endl;
            break;
        }
    }

    if(!found)
        cout << "-1" << endl;
    
    return 0;
}

