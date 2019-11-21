#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
using board_t = vector<vector<T>>;

void spring(board_t<int>& land, board_t<vector<int>>& trees, board_t<vector<int>>& deads)
{
    const int N = land.size();

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            deads[i][j].clear();
            sort(trees[i][j].begin(), trees[i][j].end());


            for(auto tree = trees[i][j].begin(); tree != trees[i][j].end();)
            {
                if(*tree <= land[i][j])
                {
                    land[i][j] -= *tree;
                    *tree += 1;
                    ++tree;
                } 
                else
                {
                    deads[i][j].push_back(*tree);
                    tree = trees[i][j].erase(tree);
                }
            }
        }
    }
}

void summer(board_t<int>& land, const board_t<vector<int>>& deads)
{
    const int N = land.size();

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            for(auto tree = deads[i][j].begin(); tree != deads[i][j].end(); ++tree)
            {
                land[i][j] += (*tree / 2);
            }
        }
    }
}

void fall(board_t<vector<int>>& trees)
{
    const int N = trees.size();
    const int di[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    const int dj[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            for(auto tree = trees[i][j].begin(); tree != trees[i][j].end(); ++tree)
            {
                if(*tree % 5 == 0)
                {
                    for(int dir = 0; dir < 8; ++dir)
                    {
                        int ni = i + di[dir];
                        int nj = j + dj[dir];
                        
                        if(ni < 0 || nj < 0 || ni >= N || nj >= N)
                            continue;
                        
                        trees[ni][nj].push_back(1);
                    }
                }
            }
        }
    }
}

void winter(board_t<int>& land, const board_t<int>& fertilize)
{
    const int N = land.size();

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            land[i][j] += fertilize[i][j];
        }
    }
}



int main(int argc, char** argv)
{
    board_t<int> land;
    board_t<int> fert;
    board_t<vector<int>> trees;
    board_t<vector<int>> deads;

    int N, M, K;
    cin >> N >> M >> K;

    land.resize(N);
    for(auto& l : land) l.resize(N, 5);
    fert.resize(N);
    for(auto& l : fert) l.resize(N, 0);
    trees.resize(N);
    for(auto& l : trees) l.resize(N);
    deads.resize(N);
    for(auto& l : deads) l.resize(N);

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cin >> fert[i][j];
        }
    }

    for(int i = 0; i < M; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;

        trees[x - 1][y - 1].push_back(z);
    }


    for(int k = 0; k < K; ++k)
    {
        spring(land, trees, deads);
        summer(land, deads);
        fall(trees);
        winter(land, fert);
    }

    int count = 0;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            count += trees[i][j].size();
        }
    }

    cout << count << endl;


    return 0;
}