#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string str;
    cin >> str;

    int sum = 0;
    bool has_zero = false;
    for(int i = 0; i < str.size(); ++i)
    {
        const int num = str[i] - '0';
        sum += num;
        if(num == 0)
            has_zero = true;
    }


    if(!has_zero || sum % 3 != 0)
    {
        cout << "-1" << endl;
    }
    else
    {
        sort(str.begin(), str.end(), std::greater<char>());
        cout << str << endl;
    }
    
    return 0;
}