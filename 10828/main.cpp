#include <iostream>
#include <vector>
#include <string>

using namespace std;

// use vector as stack
using stack_t = vector<int>;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);


    stack_t stack;
    stack.reserve(10000);

    size_t N;
    cin >> N;

    for(size_t n = 0; n < N; ++n)
    {
        std::string op;
        int param;

        cin >> op;
        if(op.compare("push") == 0)
        {
            cin >> param;

            stack.push_back(param);
        }
        else if(op.compare("pop") == 0)
        {
            if(stack.size() == 0)
            {
                cout << "-1\n";
            }
            else
            {
                param = stack.back();
                stack.pop_back();
                cout << param << '\n';
            }
        }
        else if(op.compare("size") == 0)
        {
            cout << stack.size() << '\n';
        }
        else if(op.compare("empty") == 0)
        {
            cout << (stack.empty() ? "1\n" : "0\n");
        }
        else if(op.compare("top") == 0)
        {
            if(stack.size() == 0)
            {
                cout << "-1\n";
            }
            else
            {
                param = stack.back();
                cout << param << '\n';
            }
        }
    }

    return 0;
}






