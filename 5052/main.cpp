#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--)
    {
        int N;
        cin >> N;

        vector<string> phone_numbers;
        phone_numbers.reserve(N);
        while(N--)
        {
            string str;
            cin >> str;

            phone_numbers.push_back(str);
        }

        sort(phone_numbers.begin(), phone_numbers.end());

        bool unique = true;
        auto prev = phone_numbers.begin();
        auto next = prev + 1;
        while(next != phone_numbers.end() && unique)
        {
            if(prev->size() < next->size())
            {
                const auto& prev_str = *prev;
                const auto& next_str = *next;
                
                bool is_subset = true;
                for(int indx = prev_str.size() - 1; indx >= 0; --indx)
                {
                    if(prev_str[indx] != next_str[indx])
                    {
                        is_subset = false;
                        break;
                    }
                }

                if(is_subset == true)
                {
                    unique = false;
                }
            }

            prev++;
            next++;
        }

        if(unique)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}
