#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <unordered_set>

using namespace std;

enum direction
{
    Up, Down, Left, Right
};

constexpr uint32_t calc_pow9(int i)
{
    uint32_t val = 1;
    while (i--)
        val *= 9;
    return val;
}

static constexpr uint32_t pow9[9] =
{ calc_pow9(0), calc_pow9(1), calc_pow9(2),
  calc_pow9(3), calc_pow9(4), calc_pow9(5),
  calc_pow9(6), calc_pow9(7), calc_pow9(8) };

struct board_t
{
    using id_t = int;

    uint32_t _state;
    size_t _zero_index;

    board_t(const array<id_t, 9> arr, size_t zero)
        : _state(0), _zero_index(zero)
    {
        for (size_t i = 0; i < arr.size(); ++i)
            _state += arr[i] * pow9[i];
    }

    board_t(const board_t& other)
        : _state(other._state), _zero_index(other._zero_index)
    {

    }

    const id_t operator[] (size_t index) const 
    { 
        return (_state / pow9[index]) % 9;
    }
    const size_t zero_index() const { return _zero_index; }

    void swap(size_t lhs, size_t rhs)
    {
        id_t left = (_state / pow9[lhs]) % 9;
        id_t right = (_state / pow9[rhs]) % 9;
        _state += pow9[lhs] * (right - left);
        _state += pow9[rhs] * (left - right);

        if (_zero_index == lhs)
            _zero_index = rhs;
        else if (_zero_index == rhs)
            _zero_index = lhs;
    }

    size_t hash() const
    {
        return _state;
    }

    bool operator == (const board_t& other) const
    {
        return _state == other._state ? true : false;
    }
};


namespace std
{
template<>
struct hash<board_t>
{
    size_t operator() (const board_t board) const
    {
        return board.hash();
    }
};
}


template<direction dir>
bool can_move(size_t zero);
template<>
bool can_move<Up>(size_t zero) { return zero / 3 == 0 ? false : true; }
template<>
bool can_move<Down>(size_t zero) { return zero / 3 == 2 ? false : true; }
template<>
bool can_move<Left>(size_t zero) { return zero % 3 == 0 ? false : true; }
template<>
bool can_move<Right>(size_t zero) { return zero % 3 == 2 ? false : true; }

template<direction dir>
size_t next(size_t zero);
template<>
size_t next<Up>(size_t zero) { return zero - 3; }
template<>
size_t next<Down>(size_t zero) { return zero + 3; }
template<>
size_t next<Left>(size_t zero) { return zero - 1; }
template<>
size_t next<Right>(size_t zero) { return zero + 1; }

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    array<int, 9> tmp_board;
    size_t tmp_zero = 0;
    for (int i = 0; i < 9; ++i)
    {
        cin >> tmp_board[i];
        if (tmp_board[i] == 0)
            tmp_zero = i;
    }

    const board_t end_state({ 1, 2, 3, 4, 5, 6, 7, 8, 0 }, 8);
    board_t init_state(tmp_board, tmp_zero);

    unordered_set<board_t> cache;

    deque<board_t> cur_tasks;
    deque<board_t> next_tasks;

    cur_tasks.push_back(init_state);

    int count = 0;
    bool found = false;
    while(!cur_tasks.empty() && !found)
    {
        while (!cur_tasks.empty() && !found)
        {
            board_t cur_board = cur_tasks.front();
            cur_tasks.pop_front();

            if (cache.find(cur_board) != cache.end())
                continue;

            if (cur_board == end_state)
            {
                found = true;
                break;
            }

            size_t cur_zero = cur_board.zero_index();
            if (can_move<Up>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Up>(cur_zero));
                next_tasks.push_back(cur_board);
                cur_board.swap(cur_zero, next<Up>(cur_zero));
            }
            if (can_move<Down>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Down>(cur_zero));
                next_tasks.push_back(cur_board);
                cur_board.swap(cur_zero, next<Down>(cur_zero));
            }
            if (can_move<Right>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Right>(cur_zero));
                next_tasks.push_back(cur_board);
                cur_board.swap(cur_zero, next<Right>(cur_zero));
            }
            if (can_move<Left>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Left>(cur_zero));
                next_tasks.push_back(cur_board);
                cur_board.swap(cur_zero, next<Left>(cur_zero));
            }

            cache.insert(cur_board);
        }

        if (!found)
        {
            cur_tasks = next_tasks;
            next_tasks.clear();
            count++;
        }
    }

    if (found)
        cout << count << '\n';
    else
        cout << "-1\n";


    return 0;
}