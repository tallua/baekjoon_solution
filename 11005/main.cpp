#include <iostream>

using namespace std;

void convert(int N, int B)
{
    if(N <= 0)
    {
        return;
    }
    
    convert(N / B, B);
    
    int val = N % B;
    if(val >= 10)
        cout << (char)('A' + (val - 10));
    else
        cout << (char)('0' + val);
}

int main(int argc, char** argv)
{
    int N, B;
    
    cin >> N >> B;

    convert(N, B);

    cout << '\n';
    
    return 0;
}