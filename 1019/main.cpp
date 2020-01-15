#include <iostream>
#include <array>

using namespace std;

array<long long, 10> count_occurence(int N)
{
    array<long long, 10> counts;
    counts.fill(0);

    int num = N;
    int base = 1;
    while((N / base) > 0)
    {
        int up = N / base;
        int down = N % base;

        if(up % 10 == 0)
            counts[0] += base * ((up / 10) - 1);
        else if (up > 0)
            counts[0] += base * (up / 10);

        for(int i = 1; i < 10; ++i)
        {
            counts[i] += base * (up / 10);
        }

        for(int i = 1; i < (up % 10); ++i)
        {
            counts[i] += base;
        }

        counts[(up % 10)] += down + 1;

        base *= 10;
    }

    return counts;
}

int main(int argc, char **argv)
{
    int N;
    cin >> N;
    array<long long, 10> counts = count_occurence(N);
    
    for(int i = 0; i < 10; ++i)
    {
        if(i != 0)
            cout << ' ';
        cout << counts[i];
    }
    cout << endl;

    return 0;
}