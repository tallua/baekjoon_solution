#include <iostream>

using namespace std;

constexpr int sep(const int& n)
{
    return (n * (n - 1) / 2);
}

int main(int argc, char** argv)
{
    int N;
    cin >> N;

    int sum = 2;
    while (sep(sum) < N)
    {
        sum++;
    }

    int child = sum % 2 == 0 ? sum - N + sep(sum - 1) : N - sep(sum - 1);

    cout << child << "/" << sum - child << endl;

    return 0;
}