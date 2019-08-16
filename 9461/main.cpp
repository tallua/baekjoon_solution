#include <iostream>
#include <array>

using namespace std;
using val_t = long long;

array<val_t, 1001> P;

int init()
{
    P[0] = 0;
    P[1] = 1;
    P[2] = 1;
    P[3] = 1;
    P[4] = 2;
    P[5] = 2;

    for(int i = 6; i < 1001; ++i)
    {
        P[i] = P[i - 1] + P[i - 5];
    }
}

int main(int argc, char** argv)
{
    init();

    int T;
    cin >> T;

    for(int t = 0; t < T; ++t)
    {
        int N;
        cin >> N;

        cout << P[N] << '\n';
    }

    return 0;
}