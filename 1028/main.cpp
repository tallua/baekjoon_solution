#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct check_t
{
    size_t pos;
    size_t count;
};

// 0 1 ... C-1
// C ...   2C-1

void count_left_down(const size_t R, const size_t C, const vector<char>& board, vector<size_t>& left, size_t pos)
{
    if(board[pos] == '0')
        return;

    if(pos % C == 0)
    {
        left[pos] = 1;
        return;
    }

    if(pos / C == R - 1)
    {
        left[pos] = 1;
        return;
    }
    
    count_left_down(R, C, board, left, pos + C - 1);
    
    left[pos] = left[pos + C - 1] + 1;
}

void count_right_down(size_t R, size_t C, const vector<char>& board, vector<size_t>& right, size_t pos)
{
    if(board[pos] == '0')
        return;

    if(pos % C == C - 1)
    {
        right[pos] = 1;
        return;
    }

    if(pos / C == R - 1)
    {
        right[pos] = 1;
        return;
    }
    
    count_right_down(R, C, board, right, pos + C + 1);
    
    right[pos] = right[pos + C + 1] + 1;
}

bool is_diamond(size_t R, size_t C, const vector<size_t>& left, const vector<size_t>& right, size_t pos, size_t size)
{
    if(left[pos] < size || right[pos] < size)
        return false;

    if(right[pos + (size - 1) * C - (size - 1)] < size || left[pos + (size - 1) * C + (size - 1)] < size)
        return false;
    
    return true;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t R, C;
    cin >> R >> C;

    vector<char> board;
    board.resize(R * C, 0);
    for(size_t r = 0; r < R; ++r)
    {
        for(size_t c = 0; c < C; ++c)
        {
            char ch;
            cin >> ch;
            board[r * C + c] = ch;
        }
    }

    vector<check_t> checklist;
    vector<size_t> left, right;
    left.resize(R * C, 0);
    right.resize(R * C, 0);
    checklist.reserve(R * C);

    for(size_t r = 0; r < R; ++r)
    {
        for(size_t c = 0; c < C; ++c)
        {
            const size_t pos = r * C + c;
            if(board[pos] == '1')
            {
                // calc left down
                if(left[pos] == 0)
                {
                    count_left_down(R, C, board, left, pos);
                }

                // calc right down
                if(right[pos] == 0)
                {
                    count_right_down(R, C, board, right, pos);
                }

                // add to checklist
                //cout << left[pos] << "-" << right[pos] << endl;
                if(left[pos] != 0 && right[pos] != 0)
                {
                    checklist.push_back({ pos, min(left[pos], right[pos]) });
                }
            }
        }
    }

    sort(checklist.begin(), checklist.end(), [](const check_t& lhs, const check_t& rhs)
    {
        return lhs.count > rhs.count;
    });

    size_t max_size = 0;
    size_t current_size = checklist.empty() ? 0 : checklist.front().count;
    while(current_size > max_size)
    {
        size_t i = 0;
        while(i < checklist.size() && checklist[i].count >= current_size)
        {
            if(is_diamond(R, C, left, right, checklist[i].pos, current_size))
            {
                max_size = current_size;
                break;
            }

            ++i;
        }

        current_size--;
    }

    cout << max_size << endl;

    return 0;
}


