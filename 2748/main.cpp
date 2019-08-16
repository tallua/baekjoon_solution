#include <iostream>

using namespace std;
using val_t = long long;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    switch(N)
    {
    case 0:
        cout << "0" << '\n';
        break;
    case 1:
        cout << "1" << '\n';
        break;
    default:
        val_t a_n = 1;
        val_t a_n_1 = 0;
        for(int n = 1; n < N; ++n)
        {
            val_t next = a_n_1 + a_n;
            a_n_1 = a_n;
            a_n = next;
        }

        cout << a_n << '\n';
        break;
    }

    return 0;
}