#include <iostream>
#include <algorithm>
#include <array>

using namespace std;
using val_t = size_t;
using result_t = long long;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    array<result_t, 2> n_1;
    result_t n_2;


    for(int n = 0; n < N; ++n)
    {
        val_t val;
        cin >> val;

        array<result_t, 2> tmp;

        switch(n)
        {
        case 0:
            tmp[0] = val;
            tmp[1] = 0;
            break;
        case 1:
            tmp[0] = val;
            tmp[1] = n_1[0] + val;
            break;

        default:
            tmp[0] = n_2 + val;
            tmp[1] = n_1[0] + val;
            break;
        }

        n_2 = max(n_1[0], n_1[1]);
        n_1 = tmp;
    }

    cout << max(n_1[0], n_1[1]) << '\n';

    return 0;
}


