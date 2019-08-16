#include <iostream>
#include <cmath>

using namespace std;

using uint = unsigned int;

void testcase()
{
    uint X, Y;
    cin >> X >> Y;

    uint diff = Y - X;
    uint root = (uint)sqrt(diff);

    if(diff == root * root)
    {
        cout << (root * 2) - 1 << endl;
    }
    else if(diff <= root * root + root)
    {
        cout << (root * 2) << endl;
    }
    else
    {
        cout << (root * 2) + 1 << endl;
    }
    

}

int main(int argc, char** argv)
{
    int T;
    cin >> T;

    for(int t = 0; t < T; ++t)
    {
        testcase();
    }

    return 0;
}