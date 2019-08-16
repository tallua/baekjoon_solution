#include <iostream>
#include <array>
#include <numeric>

#define DIV 1000000000

using namespace std;
using val_t = long long;

int main(int argc, char** argv)
{

    int N;
    cin >> N;

    array<val_t, 10> count;
    count.fill(1);
    count[0] = 0;

    for(int n = 1; n < N; ++n)
    {
        array<val_t, 10> tmp;
        // appending at the end
        for(size_t end = 0; end < 10; ++end)
        {
            switch(end)
            {
            case 0:
                tmp[0] = count[1];
                break;
            case 9:
                tmp[9] = count[8];
                break;
            default:
                tmp[end] = count[end - 1] + count[end + 1];
                break;
            }
            tmp[end] = tmp[end] % DIV;
        }
        count = tmp;
    }
    
    // becareful of (val_t)0 cause std::accumulate use type inference on that
    cout << accumulate(count.begin(), count.end(), (val_t)0) % DIV << '\n';

    return 0;
}