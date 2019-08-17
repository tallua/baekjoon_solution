#include <iostream>
#include <array>

using namespace std;
using val_t = unsigned int;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    // never thought about jumping 2 cups of wine.
    array<val_t, 2> buffer;
    buffer[0] = 0; // n -1
    buffer[1] = 0; // n - 2
    array<val_t, 2> last;
    cin >> last[0];
    last[1] = 0;

    for(int n = 1; n < N; ++n)
    {
        val_t now;
        cin >> now;

        val_t skip = max(buffer[0], buffer[1]) + now;
        val_t noskip = last[0] + now;
        
        buffer[1] = buffer[0];
        buffer[0] = max(last[0], last[1]);
        last[0] = skip;
        last[1] = noskip;
    }

    cout << max(max(buffer[0], buffer[1]), max(last[0], last[1])) << '\n';

    return 0;
}