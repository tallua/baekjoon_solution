#include <iostream>
#include <vector>


using namespace std;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;


    vector<int> buffer;
    buffer.resize(N);

    for(int n = 0; n < N; ++n)
    {
        cin >> buffer[n];
    }

    vector<int> nge;
    nge.resize(N, -1);

    vector<int> stack;
    stack.reserve(N);

    for(int n = N - 1; n >= 0; --n)
    {
        int val = buffer[n];

        while(stack.size() != 0 && stack.back() <= val)
        {
            stack.pop_back();
        }

        if(stack.size() == 0)
        {
            //nge[n] = -1;
            stack.push_back(val);
            continue;
        }
        else
        {
            nge[n] = stack.back();
            stack.push_back(val);
        }
    }
    
    cout << nge[0];
    for(int n = 1; n < N; ++n)
    {
        cout << ' ' << nge[n];
    }
    cout << '\n';

    return 0;
}


