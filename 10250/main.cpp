#include <iostream>
#include <iomanip>

using namespace std;

void casemain()
{
    int H, W, N;
    cin >> H >> W >> N;

    int quot = ((N - 1) / H) + 1;
    int rmnd = ((N - 1) % H) + 1;

    cout << rmnd << setfill('0') << setw(2) << quot << endl;
}

int main(int argc, char** argv)
{
    int T;
    cin >> T;

    for(int t = 0; t < T; ++t)
    {
        casemain();
    }

    return 0;
}