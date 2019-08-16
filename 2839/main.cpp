#include <iostream>

using namespace std;

int under10[] = 
{ 0, -1, -1, 1, -1, 1, 2, -1, 2, 3};

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    if(N < 10)
    {
        cout << under10[N] << endl;
    }
    else
    {
        int quotient = N / 3;
        int remainder = N % 3;

        int x = quotient;
        switch(remainder)
        {
        case 0:
            // N = 3 * x
            cout << (x / 5) * 3 + (x % 5) << endl;
            break;
        case 1:
            // N = 3 * x + 1 = 3 * (x - 3) + 5 * 2
            x = x - 3;
            cout << (x / 5) * 3 + (x % 5) + 2<< endl;
            break;
        case 2:
            // N = 3 * x + 2 = 3 * (x - 1) + 5
            x = x - 1;
            cout << (x / 5) * 3 + (x % 5) + 1<< endl;
            break;
        }
    }
    
    return 0;
}