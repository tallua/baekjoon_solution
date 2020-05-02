#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;
using DPArray = array<int, 13>;

const vector<vector<pair<int, int>>> dpmap = {
    {{1, 1}, {1, 3}, {1, 2}, {2, 4}, {2, 6}, {2, 6}, {2, 4}, {2, 5}, {2, 5}},
    {{1, 4}, {1, 6}, {1, 7}, {3, 0}},
    {{3, 0}, {3, 0}},
    {{1, 6}, {1, 4}, {1, 8}, {3, 0}},
    {{2, 0}, {1, 10}, {3, 1}, {4, 6}},
    {{2, 0}, {1, 10}, {1, 11}, {4, 4},  {4, 6}},
    {{2, 0}, {1, 11}, {3, 3}, {4, 4}},
    {{2, 0}, {1, 12}, {4, 6}},
    {{2, 0}, {1, 9}, {4, 4}},
    {{2, 1}, {2, 2}, {3, 4}},
    {{2, 2}, {2, 1}},
    {{2, 2}, {2, 3}},
    {{2, 3}, {2, 2}, {3, 6}}
};


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    DPArray current;
    current.fill(0);
    current[0] = 1;

    DPArray next[4];
    for(int i = 0; i < 4; ++i)
    {
        next[i].fill(0);
    }

    for(int n = 0; n < N; ++n)
    {
        for(int i = 0; i < dpmap.size(); ++i)
        {
            const int current_order = i;
            for(int j = 0; j < dpmap[i].size(); ++j)
            {
                const int next_index = dpmap[i][j].first - 1;
                const int next_order = dpmap[i][j].second;

                next[next_index][next_order] += current[current_order];
                next[next_index][next_order] %= 1000000;
            }
        }

        swap(current, next[0]);
        swap(next[0], next[1]);
        swap(next[1], next[2]);
        swap(next[2], next[3]);
        next[3].fill(0);

        //for(int j = 0; j < current.size(); ++j)
        //{
        //    cout << current[j] << ' ';
        //}
        //cout << endl;
        //for(int i = 0; i < 4; ++i)
        //{
        //    for(int j = 0; j < next[i].size(); ++j)
        //    {
        //        cout << next[i][j] << ' ';
        //    }
        //    cout << endl;
        //}
        //
        //cout << "-----------------" << endl;
    }

    cout << current[0] << endl;
    
    return 0;
}