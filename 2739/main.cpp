#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    for(int mult = 1; mult <= 9; ++mult)
    {
        cout << N << " * " << mult << " = " << (N * mult) << '\n';
    }
    
    return 0;
}


