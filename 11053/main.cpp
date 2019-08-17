#include <iostream>
#include <array>

using namespace std;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    int max_index = 0;
    array<int, 1001> max_val;
    max_val.fill(0);
    for(int n = 0; n < N; ++n)
    {
        int val;
        cin >> val;

        for(int index = max_index; index >= 0; --index)
        {
            if(max_val[index] < val)
            {
                max_val[index + 1] = val;
                if(index + 1 > max_index)
                    max_index = index + 1;
                
                break;
            }
        }

    }

    cout << max_index << '\n';

    return 0;
}