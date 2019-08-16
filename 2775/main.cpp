#include <iostream>
#include <array>

using namespace std;


// 1  5 15 35 70
// 1  4 10 20 35
// 1  3  6 10 15
// 1  2  3  4  5
#define LEN_X 14
#define LEN_Y 15

array<array<int, LEN_X>, LEN_Y> arr;

void init()
{
    for(int x = 0; x < LEN_X; ++x)
    {
        arr[0][x] = x + 1;
    }
    for(int y = 0; y < LEN_Y; ++y)
    {
        arr[y][0] = 1;
    }

    for(int y = 1; y < LEN_Y; ++y)
    {
        for(int x = 1; x < LEN_X; ++x)
        {
            arr[y][x] = arr[y - 1][x] + arr[y][x - 1];
        }
    }
}

void casemain()
{
    int k, n;
    cin >> k;
    cin >> n;
    cout << arr[k][n - 1] << endl;
}


int main(int argc, char** argv)
{
    init();

    int T;
    cin >> T;
    for(int t = 0; t < T; ++t)
    {
        casemain();
    }

    return 0;
}




