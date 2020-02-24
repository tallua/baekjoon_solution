#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);
    

    string out;
    vector<int> cnt_arr;
    int cnt = 0;
    char prev = str[0];
    for(size_t i = 0; i < str.size(); ++i)
    {
        if(str[i] == prev)
            cnt++;
        else
        {
            out += prev;
            cnt_arr.push_back(cnt);

            prev = str[i];
            cnt = 1;
        }
    }
            
            
    out += prev;
    cnt_arr.push_back(cnt);

    cout << '\"' << out << "\"\n";

    cout << '[';
    for(size_t i = 0; i < cnt_arr.size(); ++i)
    {
        cout << cnt_arr[i];
        if(i != cnt_arr.size() - 1)
            cout << ',';
    }


}