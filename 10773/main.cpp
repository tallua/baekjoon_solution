#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

using stack_t = vector<int>;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    stack_t stack;
    stack.reserve(100000);

    size_t K;
    cin >> K;

    for(size_t k = 0; k < K; ++k)
    {
        int val;
        cin >> val;

        if(val == 0)
        {
            stack.pop_back();
        }
        else
        {
            stack.push_back(val);
        }
        
    }

    long long result = std::accumulate(stack.begin(), stack.end(), 0LL);
    cout << result << '\n';

    return 0;
}