#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

using board_t = vector<vector<int>>;

int main(int argc, char** argv)
{
    int N, L;
    cin >> N >> L;

    board_t board;
    board_t board_trans;
    board.resize(N);
    for(auto& l : board) l.resize(N, 0);
    board_trans.resize(N);
    for(auto& l : board_trans) l.resize(N, 0);

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            int tmp;
            cin >> tmp;
            board[i][j] = tmp;
            board_trans[j][i] = tmp;
        }
    }
    
    
    auto has_path = [&](auto begin, auto end) -> bool
    {
        enum { idle, dec } state = idle;
        
        auto it = begin;
        int prev = *it;
        int cnt = 0;
        while(it != end)
        {
            if(state == idle)
            {
                
                if(*it == prev)
                    cnt++;
                else if(*it > prev && *it - prev == 1)
                {
                    if(cnt < L)
                        return false;
                    cnt = 1;
                }
                else if(*it < prev && prev - *it == 1)
                {
                    state = dec;
                    cnt = L - 1;
                    if(cnt == 0)
                    {
                        state = idle;
                    }
                }
                else
                {
                    return false;
                }
            }
            else if(state == dec)
            {
                if(prev != *it)
                    return false;
                cnt--;
                if(cnt == 0)
                {
                    state = idle;
                }
            }

            prev = *it;
            it++;
        }

        if(state == idle)
            return true;
        return false;
    };


    int result = 0;
    for(int i = 0; i < N; ++i)
    {
        if(has_path(board[i].begin(), board[i].end()))
            result++;
        if(has_path(board_trans[i].begin(), board_trans[i].end()))
            result++;
    }

    cout << result << endl;


    return 0;
}