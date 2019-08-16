#include <iostream>
#include <array>

using namespace std;

using val_t = long long;

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    switch(N)
    {
    case 1:
        cout << "1" << '\n';
        break;
    case 2:
        cout << "2" << '\n';
        break;
    default:
        val_t a_n_1 = 1;
        val_t a_n = 2;

        for(int i = 2; i < N; ++i)
        {
            val_t tmp = a_n + a_n_1;
            a_n_1 = a_n;
            a_n = tmp;

            a_n = a_n % 15746;
        }

        cout << a_n << '\n';
    }

    return 0;
}