#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <algorithm>

using namespace std;

enum direction
{
    Up,
    Down,
    Left,
    Right
};

template <direction dir>
bool can_move(size_t zero);
template <>
bool can_move<Up>(size_t zero) { return zero / 3 == 0 ? false : true; }
template <>
bool can_move<Down>(size_t zero) { return zero / 3 == 2 ? false : true; }
template <>
bool can_move<Left>(size_t zero) { return zero % 3 == 0 ? false : true; }
template <>
bool can_move<Right>(size_t zero) { return zero % 3 == 2 ? false : true; }

template <direction dir>
size_t next(size_t zero);
template <>
size_t next<Up>(size_t zero) { return zero - 3; }
template <>
size_t next<Down>(size_t zero) { return zero + 3; }
template <>
size_t next<Left>(size_t zero) { return zero - 1; }
template <>
size_t next<Right>(size_t zero) { return zero + 1; }

template <int N>
struct F { enum { val = N * F<N - 1>::val }; };

template <>
struct F<0> { enum { val = 1 }; };

constexpr size_t calc_pow(int base, int exp)
{
    size_t val = 1;
    while (exp--)
        val *= base;
    return val;
}

const size_t factorial[9]{
    F<1>::val, F<2>::val, F<3>::val,
    F<4>::val, F<5>::val, F<6>::val,
    F<7>::val, F<8>::val, F<9>::val };

constexpr size_t pow9[9]{
    calc_pow(9, 0), calc_pow(9, 1), calc_pow(9, 2),
    calc_pow(9, 3), calc_pow(9, 4), calc_pow(9, 5),
    calc_pow(9, 6), calc_pow(9, 7), calc_pow(9, 8) };

struct board_t
{
    using encoded_t = size_t;
    const static size_t max_encoded_count = 3628800;

    size_t _state;
    size_t _zero_index;

    board_t(const array<int, 9> arr, size_t zero)
        : _state(0), _zero_index(zero)
    {
        for (size_t i = 0; i < arr.size(); ++i)
            _state += arr[i] * pow9[i];
    }

    board_t(const board_t& other)
        : _state(other._state), _zero_index(other._zero_index)
    {
    }

    const size_t zero_index() const
    {
        return _zero_index;
    }

    void swap(size_t lhs, size_t rhs)
    {
        auto left = (_state / pow9[lhs]) % 9;
        auto right = (_state / pow9[rhs]) % 9;
        _state += pow9[lhs] * (right - left);
        _state += pow9[rhs] * (left - right);

        if (_zero_index == lhs)
            _zero_index = rhs;
        else if (_zero_index == rhs)
            _zero_index = lhs;
    }

    size_t encode() const
    {
        size_t result = 0;

        for (size_t i = 0; i < 9; ++i)
        {
            result += ((_state / pow9[i]) % 9) * factorial[i];
        }

        return result;
    }
};

array<bool, board_t::max_encoded_count> visited;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    visited.fill(false);

    array<int, 9> init_arr;
    size_t init_zero = 0;
    for (int i = 0; i < 9; ++i)
    {
        cin >> init_arr[i];
        if (init_arr[i] == 0)
            init_zero = i;
    }

    const board_t init_state(init_arr, init_zero);
    const board_t end_state({ 1, 2, 3, 4, 5, 6, 7, 8, 0 }, 8);
    const auto end_state_code = end_state.encode();


    deque<board_t> cur_tasks;
    deque<board_t> next_tasks;
    visited[init_state.encode()] = true;
    cur_tasks.push_back(init_state);

    int count = 0;
    bool found = false;
    while (!cur_tasks.empty() && !found)
    {
        while (!cur_tasks.empty() && !found)
        {
            board_t cur_board = cur_tasks.front();
            cur_tasks.pop_front();

            auto cur_code = cur_board.encode();
            if (cur_code == end_state_code)
            {
                found = true;
                break;
            }

            size_t cur_zero = cur_board.zero_index();
            if (can_move<Up>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Up>(cur_zero));
                const auto next_code = cur_board.encode();
                if(visited[next_code] == false)
                {
                    visited[next_code] = true;
                    next_tasks.push_back(cur_board);
                }
                cur_board.swap(cur_zero, next<Up>(cur_zero));
            }
            if (can_move<Down>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Down>(cur_zero));
                const auto next_code = cur_board.encode();
                if(visited[next_code] == false)
                {
                    visited[next_code] = true;
                    next_tasks.push_back(cur_board);
                }
                cur_board.swap(cur_zero, next<Down>(cur_zero));
            }
            if (can_move<Right>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Right>(cur_zero));
                const auto next_code = cur_board.encode();
                if(visited[next_code] == false)
                {
                    visited[next_code] = true;
                    next_tasks.push_back(cur_board);
                }
                cur_board.swap(cur_zero, next<Right>(cur_zero));
            }
            if (can_move<Left>(cur_zero))
            {
                cur_board.swap(cur_zero, next<Left>(cur_zero));
                const auto next_code = cur_board.encode();
                if(visited[next_code] == false)
                {
                    visited[next_code] = true;
                    next_tasks.push_back(cur_board);
                }
                cur_board.swap(cur_zero, next<Left>(cur_zero));
            }

            visited[cur_code] = true;
        }

        if (!found)
        {
            std::swap(cur_tasks, next_tasks);
            count++;
        }
    }

    if (found)
        cout << count << '\n';
    else
        cout << "-1\n";

    return 0;
}