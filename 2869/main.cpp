#include <iostream>
#include <cmath>

using namespace std;



int main(int argc, char** argv)
{
    int A, B, V;
    cin >> A >> B >> V;

    // a(x) = A + (A - B)(x - 1) >= V arg_min(x)
    cout << (int)ceil((double)(V - A) / (A - B)) + 1 << endl;

    return 0;
}