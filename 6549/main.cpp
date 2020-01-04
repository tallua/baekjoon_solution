#include <iostream>
#include <vector>

using namespace std;
using len_t = long long;

int main(int argc, char **argv)
{
    while (true)
    {
        cin.tie(NULL);
        ios::sync_with_stdio(false);
        
        int N;
        cin >> N;

        if (N == 0)
            break;

        vector<pair<len_t, int>> height_stack;
        height_stack.reserve(N);
        len_t max_area = 0;

        for (int n = 0; n <= N; ++n)
        {
            len_t current_height = 0;
            int current_start = n;

            if (n != N)
                cin >> current_height;

            while (!height_stack.empty() && height_stack.back().first > current_height)
            {
                auto popped_height = height_stack.back();
                height_stack.pop_back();

                len_t popped_area = popped_height.first * (n - popped_height.second);
                max_area = max(max_area, popped_area);
                current_start = min(current_start, popped_height.second);
            }

            if (height_stack.empty() || height_stack.back().first != current_height)
            {
                height_stack.push_back(make_pair(current_height, current_start));
            }
        }

        cout << max_area << endl;
    }

    return 0;
}