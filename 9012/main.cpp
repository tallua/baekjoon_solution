#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t T;
    cin >> T;

    for(size_t t = 0; t < T; ++t)
    {
        string buf;
        cin >> buf;

        size_t len = buf.length();
        size_t cnt = 0;
        bool ok = true;
        for(size_t i = 0; i < len; ++i)
        {
            char c = buf[i];
            if(c == '(')
            {
                cnt++;
            }
            else
            {
                if(cnt == 0)
                {
                    ok = false;
                    break;
                }
                else
                {
                    cnt--;
                }
                
            }
        }

        if(ok == true && cnt == 0)
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