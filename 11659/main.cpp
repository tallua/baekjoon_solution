#include <iostream>
#include <array>

using namespace std;


int main(int argc, char** argv)
{
    // WTF
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    
    array<int, 100000> arr;
    //arr.resize(N + 1, 0);

    arr[0] = 0;
    for(int n = 1; n < N + 1; ++n)
    {
        int tmp = 0;
        cin >> tmp;
        arr[n] = arr[n - 1] + tmp;
    }

    for(int m = 0; m < M; ++m)
    {
        int i, j;
        cin >> i >> j;

        int min = i < j ? i : j;
        int max = i < j ? j : i;

        int sum = arr[max] - arr[min - 1];

        cout << sum << '\n';
    }
    
    return 0;
}

