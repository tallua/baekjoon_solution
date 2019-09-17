#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char** argv)
{
    int N, K;
    cin >> N >> K;

    deque<int> cq;
    for(int n = 1; n <= N; ++n)
        cq.push_back(n);

    int k = 0;
    bool is_first_out = true;
    while(cq.size() != 0)
    {
        k++;
        if(k == K)
        {
            int val = cq.front();
            cq.pop_front();

            if(is_first_out)
            {
                cout << "<" << val;
                is_first_out = false;
            }
            else
            {
                cout << ", " << val;
            }

            k = 0;
        }
        else
        {
            cq.push_back(cq.front());
            cq.pop_front();
        }
    }

    cout << ">\n";

    return 0;
}
