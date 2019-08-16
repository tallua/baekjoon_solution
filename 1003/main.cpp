#include <iostream>
#include <array>

using namespace std;

array<size_t, 41> count_0;
array<size_t, 41> count_1;

void init()
{
    count_0[0] = 1;
    count_0[1] = 0;
    count_1[0] = 0;
    count_1[1] = 1;

    for(int i = 2; i < 41; ++i)
    {
        count_0[i] = count_0[i - 1] + count_0[i - 2];
        count_1[i] = count_1[i - 1] + count_1[i - 2];
    }
}

int main(int argc, char** argv)
{
    init();

    int T;
    cin >> T;

    for(int t = 0; t < T; ++t)
    {
        int n;
        cin >> n;

        cout << count_0[n] << " " << count_1[n] << endl;
    }

    return 0;
}