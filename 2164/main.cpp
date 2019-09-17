#include <iostream>

using namespace std;

int g(int n);
int f(int n);

// dont discard first
int g(int n)
{
    if(n == 1)
        return 1;

    if(n % 2 == 0)
        return 2 * g(n / 2) - 1;
    return 2 * f((n + 1) / 2) - 1;
}

// discard first
int f(int n)
{
    if(n == 1)
        return 1;
        
    if(n % 2 == 0)
        return 2 * f(n / 2);
    return 2 * g((n - 1) / 2);
}

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    cout << f(N) << '\n';

    return 0;
}