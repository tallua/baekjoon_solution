#include <iostream>
#include <vector>

using namespace std;

struct comp
{
    int val;
    int count;
};

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    long long count = 0;
    vector<comp> stack;
    for (int n = 0; n < N; ++n)
    {
        int current;
        cin >> current;

        while(!stack.empty() && stack.back().val < current)
        {
            count += stack.back().count;
            stack.pop_back();
        }

        comp tmp;
        tmp.val = current;
        tmp.count = 1;

        if(!stack.empty() && stack.back().val == current)
        {
            count += stack.back().count;
            tmp.count += stack.back().count;
            stack.pop_back();
        }

        if(!stack.empty())
            count += 1;

        stack.push_back(tmp);
    }

    cout << count << endl;

    return 0;
}
