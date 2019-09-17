#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    deque<int> queue;

    for(int n = 0; n < N; ++n)
    {
        string op;
        cin >> op;

        if(op == "push")
        {
            int x;
            cin >> x;

            queue.push_back(x);
        }
        else if(op == "pop")
        {
            if(queue.size() == 0)
            {
                cout << "-1\n";
            }
            else
            {
                cout << queue.front() << '\n';
                queue.pop_front();
            }
            
        }
        else if(op == "size")
        {
            cout << queue.size() << '\n';
        }
        else if(op == "empty")
        {
            cout << (queue.empty() ? 1 : 0) << '\n';
        }
        else if(op == "front")
        {
            if(queue.size() == 0)
            {
                cout << "-1\n";
            }
            else
            {
                cout << queue.front() << '\n';
            }
        }
        else if(op == "back")
        {
            if(queue.size() == 0)
            {
                cout << "-1\n";
            }
            else
            {
                cout << queue.back() << '\n';
            }
        }
    }

    return 0;
}



