#include <iostream>

using namespace std;

constexpr int sep(const int& n)
{
    return (3 * n * (n + 1)) + 1;
}

#define MAX_SEP 18258

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    for(int i = 0; i < MAX_SEP; ++i)
    {
        if(sep(i) >= N)
        {
            cout << i + 1 << endl;
            break;
        }
    }

    return 0;
}