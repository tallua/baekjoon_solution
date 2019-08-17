#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    int sum = 0;
    int max = -10000000;
    for(int n = 0; n < N; ++n)
    {
        int now;
        cin >> now;

        int sum_now = sum + now;
        if(sum_now < 0)
        {
            sum = 0;
            if(max < now)
                max = now;
        }
        else
        {
            sum = sum_now;
            if(max < sum_now)
                max = sum_now;
        }
    }

    cout << max << '\n';

    return 0;
}
