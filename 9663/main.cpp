#include <iostream>
#include <vector>
#include <utility>

using namespace std;

bool available(const vector<pair<int, int>>& queens, const pair<int, int>& pos)
{
    for(int i = 0; i < queens.size(); ++i)
    {
        auto& queen = queens[i];
        if(queen.first == pos.first)
            return false;
            
        //if(queen.second == pos.second)
        //    return false;

        if(queen.first + queen.second == pos.first + pos.second)
            return false;
            
        if(queen.first - queen.second == pos.first - pos.second)
            return false;
    }

    return true;
}

size_t NQueen(const size_t N, vector<pair<int, int>>& queens)
{
    size_t nth = queens.size();
    if(nth == N)
        return 1;

    size_t sum = 0;
    for(int i = 0; i < N; ++i)
    {
        auto pos = make_pair(i, nth);
        if(available(queens, pos))
        {
            queens.push_back(pos);
            sum += NQueen(N, queens);
            queens.pop_back();
        }
    }

    return sum;
}


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    vector<pair<int, int>> queens;
    queens.reserve(16);
    cout << NQueen(N, queens) << '\n';

    return 0;
}


