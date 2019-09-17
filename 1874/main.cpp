#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    vector<int> out_stack;
    out_stack.resize(N);
    for(int n = 0; n < N; ++n)
    {
        out_stack[n] = N - n;
    }

    vector<int> in_stack;
    in_stack.reserve(N);


    vector<char> result;
    result.reserve(2 * N);
    
    bool failed = false;
    for(int n = 0; n < N; ++n)
    {
        int next;
        cin >> next;
        
        while(true)
        {
        
            int top = in_stack.back();
            if(top == next)
            {
                in_stack.pop_back();
                result.push_back('-');
                break;
            }
            else if(top < next)
            {
                if(out_stack.size() == 0)
                {
                    failed = true;
                    break;
                }

                int tmp = out_stack.back();
                out_stack.pop_back();
                in_stack.push_back(tmp);
                result.push_back('+');
            }
            else
            {
                failed = true;
                break;
            }
            
        }

        if(failed)
        {
            break;
        }
    }

    if(failed)
    {
        cout << "NO\n";
    }
    else
    {
        for(size_t i = 0; i < result.size(); ++i)
        {
            cout << result[i] << '\n';
        }
    }
    

    return 0;
}