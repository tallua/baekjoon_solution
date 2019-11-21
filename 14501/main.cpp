#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    vector<int> days;
    vector<int> costs;

    for(int n = 0; n < N; ++n)
    {
        int d, c;
        cin >> d >> c;
        days.push_back(d);
        costs.push_back(c);
    }


    vector<int> dp_arr;
    dp_arr.resize(N, 0);

    for(int n = N - 1; n >= 0; --n)
    {
        int end = n + days[n] - 1;
        int cost = 0;
        if(end < N)
        {
            cost += costs[n];
        }
        if(end + 1 < N)
        {
            cost += dp_arr[end + 1];
        }

        if(n + 1 < N)
            dp_arr[n] = std::max(cost, dp_arr[n + 1]);
        else
            dp_arr[n] = cost;
    }

    cout << dp_arr[0] << endl;
    
    return 0;
}