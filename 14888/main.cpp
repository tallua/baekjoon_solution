#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main(int argc, char** argv)
{
    int N;
    cin >> N;


    vector<int> arr;
    arr.resize(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }


    int add, sub, mul, div;
    cin >> add >> sub >> mul >> div;
    vector<int> ops;
    ops.reserve(add + sub + mul + div);
    fill_n(back_inserter(ops), add, 1);
    fill_n(back_inserter(ops), sub, 2);
    fill_n(back_inserter(ops), mul, 3);
    fill_n(back_inserter(ops), div, 4);

    int min_val = INT32_MAX;
    int max_val = INT32_MIN;

    do {
        int result = arr[0];
        for (int i = 0; i < N - 1; ++i)
        {
            switch (ops[i])
            {
            case 1:
                result += arr[i + 1];
                break;
            case 2:
                result -= arr[i + 1];
                break;
            case 3:
                result *= arr[i + 1];
                break;
            case 4:
                result /= arr[i + 1];
                break;
            }
        }

        min_val = min(min_val, result);
        max_val = max(max_val, result);

    } while (next_permutation(ops.begin(), ops.end()));

    cout << max_val << '\n';
    cout << min_val << '\n';

    return 0;
}