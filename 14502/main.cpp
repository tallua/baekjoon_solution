#include <iostream>
#include <vector>
#include <deque>

using namespace std;


void floodfill(vector<vector<int>>& board)
{
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};

    const size_t N = board.size();
    const size_t M = board[0].size();

    deque<int> polluted;
    for(int n = 0; n < N; ++n)
    {
        for(int m = 0; m < M; ++m)
        {
            if(board[n][m] == 2)
            {
                polluted.push_back(m  + n * M);
            }
        }
    }

    while(!polluted.empty())
    {
        int p = polluted.front();
        polluted.pop_front();

        int x = p % M;
        int y = p / M;

        for(int dir = 0; dir < 4; ++dir)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(nx < 0 || ny < 0 || nx >= M || ny >= N)
                continue;

            if(board[ny][nx] == 0)
            {
                board[ny][nx] = 2;
                polluted.push_back(nx + ny * M);
            }
        }
    }
}

int dfs(vector<vector<int>>& board, int sp, int count)
{
    const size_t N = board.size();
    const size_t M = board[0].size();

    if(count == 3)
    {
        vector<vector<int>> copy = board;
        floodfill(copy);
        int count = 0;
        for(int n = 0; n < N; ++n)
        {
            for(int m = 0; m < M; ++m)
            {
                if(copy[n][m] == 0)
                {
                    count++;
                }
            }
        }
        return count;
    }

    int max = 0;
    for(int current = sp; current < N * M; ++current)
    {
        int x = current % M;
        int y = current / M;

        if(board[y][x] == 0)
        {
            board[y][x] = 1;
            int tmp = dfs(board, current + 1, count + 1);
            board[y][x] = 0;

            max = std::max(max, tmp);
        }
    }

    return max;
}



int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> board;
    board.resize(N);
    for(auto& l : board) l.resize(M, 0);
    for(int n = 0; n < N; ++n)
    {
        for(int m = 0; m < M; ++m)
        {
            cin >> board[n][m];
        }
    }

    int result = dfs(board, 0, 0);
    cout << result << endl;

    return 0;
}