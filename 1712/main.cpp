#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
    int BASE, COST, BENEFIT;
    cin >> BASE >> COST >> BENEFIT;

    if(BENEFIT <= COST)
    {
        cout << "-1" << endl;
    }
    else
    {
        // BASE + COST * x < BENEFIT * x
        // BASE < (BENEFIT - COST) * x
        int cnt = floor(1 + ((double) BASE / (BENEFIT - COST)));
        cout << cnt << endl;
    }
    return 0;
}
