#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, L;
    cin >> N >> L;

    int min_index = -1;
    int min_value= -1000000000;

    deque<pair<int, int>> window;

    for(int i = 0; i < N; ++i)
    {
        int tmp;
        cin >> tmp;

        while(window.size() != 0 && window.back().second > tmp)
        {
            window.pop_back();
        }

        window.push_back(make_pair(i, tmp));

        while(window.size() != 0 && i - window.front().first >= L)
        {
            window.pop_front();
        }

        // print min
        cout << window.front().second << ' ';
    }

    cout << endl;

    return 0;
}

