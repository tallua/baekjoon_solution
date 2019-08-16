#include <iostream>


using namespace std;


// <x:y>
// x = K % M -> K = M * m + x
// y = K % N -> K = N * n + y
// M * m + x = K = N * n + y
// m = (N * n + (y - x)) / M

void casemain()
{
    int x, y, M, N;
    cin >> M >> N >> x >> y;

    int n_found = -1;
    for(int n = 0; n < M; ++n)
    {
        if(((N * n) + (y - x)) % M == 0)
        {
            n_found = n;
            break;
        }
    }

    if(n_found == -1)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << (N * n_found) + y << endl;
    }
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