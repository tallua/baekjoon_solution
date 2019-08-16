#include <iostream>
#include <deque>

using namespace std;

struct Work
{
    int val;
    size_t count;
};

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    deque<Work> process;
    process.push_back({N, 0});

    size_t count = 0;
    while(true)
    {
        Work w = process.front();
        process.pop_front();

        if(w.val == 1)
        {
            cout << w.count << '\n';
            break;
        }

        if(w.val % 3 == 0)
            process.push_back({w.val / 3, w.count + 1});
        if(w.val % 2 == 0)
            process.push_back({w.val / 2, w.count + 1});
        if(w.val > 2)
            process.push_back({w.val - 1, w.count + 1});

    }

    return 0;
}
